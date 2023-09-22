using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.IO;
using System.Collections;
using System.Drawing.Imaging;
using System.Windows.Forms.VisualStyles;



namespace MasterUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        // SerialPort 
        SerialPort serialport = new SerialPort("COM5", 115200, Parity.None, 8, StopBits.One);
        // Image system
        int imageWidth = 240;
        int imageLength = 320;
        private byte[] imagedata = null;
        Bitmap result = null;
        private int[,] rgbhex = null;
        string filePath = string.Empty;

        // Image process
        public int[,] Bitmap2RGBdata(Bitmap bimage) 
        {
            // convert bitmap to rgb array
            int Height = bimage.Height; // 320
            int Width = bimage.Width; //240
            int[,,] rgbData = new int[Width, Height, 3];
            int[,] rgbhexData = new int[Width, Height];
            
            for (int y = 0; y < Height; y++)
            {
                for (int x = 0; x < Width; x++)
                {
                    Color color = bimage.GetPixel(x, y);
                    rgbData[x, y, 0] = (color.R) / 8;
                    rgbData[x, y, 1] = (color.G) / 4;
                    rgbData[x, y, 2] = (color.B) / 8;
                    rgbhexData[x, y] = (((rgbData[x, y, 0] << 6)) | (rgbData[x, y, 1])) << 5 | (rgbData[x, y, 2]);
                    // R contain 5 btis G contain 6 bits B contain 5 bits
                }
            }
            this.rgbhex= rgbhexData;
            return rgbhexData;        
        }
        // UI function
        private void Load_Click(object sender, EventArgs e)
        {
            // laod image
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.InitialDirectory = "D\\rojects";
            ofd.Filter = "*.jpg |*.JPG|*.png|*.PNG";
            //ofd.Filter = "*.png|*.PNG";
            ofd.FilterIndex = 2;
            ofd.RestoreDirectory = true;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                filePath = ofd.FileName;
            }
            // load image to bitmap
            FileStream fs = new FileStream(filePath, FileMode.Open);
            BinaryReader br = new BinaryReader(fs);
            imagedata = br.ReadBytes(Convert.ToInt32(fs.Length)); //byte []
            MemoryStream ms = new MemoryStream(imagedata);
            Bitmap img = new Bitmap(ms); // bitmap

            // resiez bitmap to fit panel and convert to hex data
            this.result = new Bitmap(img, new Size(this.imageWidth, this.imageLength));
            int[,] array = Bitmap2RGBdata(result);
            // show imagwe to picturebox
            pictureBox2.Image = result;
            fs.Close();
        }
        private void Send_Click(object sender, EventArgs e)
        {
            int Width = this.rgbhex.GetLength(1); //240
            int Height = this.rgbhex.GetLength(0); //320
            serialport.Open();
            int usart_data = 0x00;
            int usart_data_sendimage_start = (usart_data | 0x60);
            byte[] b_start = BitConverter.GetBytes(usart_data_sendimage_start);
            serialport.Write(b_start, 0, 1);
            for (int y = 0; y < Width ; y++)
            {
                for (int x = 0; x < Height; x++)
                {
                    int usart_data_sendimage_data1 = (usart_data | (0x10)) | ((this.rgbhex[x, y]) & 0xF);
                    byte[] b_data1 = BitConverter.GetBytes(usart_data_sendimage_data1);
                    serialport.Write(b_data1, 0, 1);
                    int usart_data_sendimage_data2 = (usart_data | (0x20)) | ((this.rgbhex[x, y] >> 4) & 0xF);
                    byte[] b_data2 = BitConverter.GetBytes(usart_data_sendimage_data2);
                    serialport.Write(b_data2, 0, 1);
                    int usart_data_sendimage_data3 = (usart_data | (0x30)) | ((this.rgbhex[x, y] >> 8) & 0xF);
                    byte[] b_data3 = BitConverter.GetBytes(usart_data_sendimage_data3);
                    serialport.Write(b_data3, 0, 1);
                    int usart_data_sendimage_data4 = (usart_data | (0x40)) | ((this.rgbhex[x, y] >> 12) & 0xF);
                    byte[] b_data4 = BitConverter.GetBytes(usart_data_sendimage_data4);               
                    serialport.Write(b_data4, 0, 1);
                    int usart_data_sendimage_save = (usart_data | 0x70);
                    byte[] b_save = BitConverter.GetBytes(usart_data_sendimage_save);
                    serialport.Write(b_save, 0, 1);
                }
                int usart_data_sendimage_show = (usart_data | 0x80);
                byte[] b_show = BitConverter.GetBytes(usart_data_sendimage_show);
                serialport.Write(b_show, 0, 1);
                Thread.Sleep(5); // ->> it would be needed to make sure ot work normally
            }
            serialport.Dispose();
            Console.WriteLine("Send finish");
            this.imagedata = null;
            this.rgbhex = null;
            this.result = null;
        }
        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void show_FullScreen_Color(char color) 
        {
            serialport.Open();
            int usart_data = 0x00;
            int usart_data_sendimage_start = (usart_data | 0x60);
            byte[] b_start = BitConverter.GetBytes(usart_data_sendimage_start);
            serialport.Write(b_start, 0, 1);
            int temp_color = 0x0000;

            switch (color) 
            {
                case 'W':
                    temp_color = 0xFFFF;
                    break;
                case 'B':
                    temp_color = 0x0000;
                    break;
                case 'r':
                    temp_color = 0xF800;
                    break;
                case 'g':
                    temp_color = 0x07E0;
                    break;
                case 'b':
                    temp_color = 0x001F;
                    break;
                default:
                    break;
            }
            int usart_data_sendimage_data1 = (usart_data | (0x10)) | ((temp_color) & 0xF);
            byte[] b_data1 = BitConverter.GetBytes(usart_data_sendimage_data1);
            serialport.Write(b_data1, 0, 1);
            int usart_data_sendimage_data2 = (usart_data | (0x20)) | ((temp_color >> 4) & 0xF);
            byte[] b_data2 = BitConverter.GetBytes(usart_data_sendimage_data2);
            serialport.Write(b_data2, 0, 1);
            int usart_data_sendimage_data3 = (usart_data | (0x30)) | ((temp_color >> 8) & 0xF);
            byte[] b_data3 = BitConverter.GetBytes(usart_data_sendimage_data3);
            serialport.Write(b_data3, 0, 1);
            int usart_data_sendimage_data4 = (usart_data | (0x40)) | ((temp_color >> 12) & 0xF);
            byte[] b_data4 = BitConverter.GetBytes(usart_data_sendimage_data4);
            serialport.Write(b_data4, 0, 1);
            int usart_data_sendimage_show = (usart_data | 0x50);
            byte[] b_show = BitConverter.GetBytes(usart_data_sendimage_show);
            serialport.Write(b_show, 0, 1);
            Thread.Sleep(5); // ->> it would be needed to make sure ot work normally

            serialport.Dispose();
            Console.WriteLine("Send finish");
            this.imagedata = null;
            this.rgbhex = null;
            this.result = null;

        }


        private void gamma1_Click(object sender, EventArgs e)
        {
            int[] init_Gamma_setting = {0x0F, 0x28, 0x29, 0x0D, 0x11, 0x09, 0x54,
                                        0xA8, 0x46, 0x0F, 0x1A, 0x0E, 0x14, 0x0C, 0x00,
                                        0x00, 0x1B, 0x1E, 0x07, 0x13, 0x07, 0x2A, 0x47,
                                        0x39, 0x03, 0x09, 0x0C, 0x35, 0x3D, 0x0F};

            serialport.Open();
            int usart_data = 0x00;
            int usart_data_sendGamma_start = (usart_data | 0xA0);
            byte[] b_start = BitConverter.GetBytes(usart_data_sendGamma_start);
            serialport.Write(b_start, 0, 1);
            for (int i = 0; i < init_Gamma_setting.Length; i++) 
            {
                int send_data1 = (usart_data | (0xA0)) | ((init_Gamma_setting[i] >> 0) & 0xF);
                int send_data2 = (usart_data | (0xB0)) | ((init_Gamma_setting[i] >> 4) & 0xF);
                int send_save  = (usart_data | (0xD0));
                byte[] b_send_data1 = BitConverter.GetBytes(send_data1);
                serialport.Write(b_send_data1, 0, 1);
                byte[] b_send_data2 = BitConverter.GetBytes(send_data2);
                serialport.Write(b_send_data2, 0, 1);
                byte[] b_send_save = BitConverter.GetBytes(send_save);
                serialport.Write(b_send_save, 0, 1);
            }
            int send_show = (usart_data | (0xC0));
            byte[] b_send_show = BitConverter.GetBytes(send_show);
            serialport.Write(b_send_show, 0, 1);
            Thread.Sleep(5); // ->> it would be needed to make sure ot work normally
            serialport.Dispose();

        }



        private void gamma2_Click(object sender, EventArgs e)
        {

            int[] init_Gamma_setting = {0x0F,0x28,0x20,0x08,0x0c,0x09,0x04,
                                        0x68,0x3f,0x25,0x10,0x07,0x14,0x0C,0x0F, 
                                        0x00,0x1B,0x17,0x03,0x0f,0x07,0x0A,
                                        0x67,0x3f,0x25,0x10,0x07,0x14,0x0D,0x0F};
            serialport.Open();
            int usart_data = 0x00;
            int usart_data_sendGamma_start = (usart_data | 0xA0);
            byte[] b_start = BitConverter.GetBytes(usart_data_sendGamma_start);
            serialport.Write(b_start, 0, 1);
            for (int i = 0; i < init_Gamma_setting.Length; i++)
            {
                int send_data1 = (usart_data | (0xA0)) | ((init_Gamma_setting[i] >> 0) & 0xF);
                int send_data2 = (usart_data | (0xB0)) | ((init_Gamma_setting[i] >> 4) & 0xF);
                int send_save = (usart_data | (0xD0));
                byte[] b_send_data1 = BitConverter.GetBytes(send_data1);
                serialport.Write(b_send_data1, 0, 1);
                byte[] b_send_data2 = BitConverter.GetBytes(send_data2);
                serialport.Write(b_send_data2, 0, 1);
                byte[] b_send_save = BitConverter.GetBytes(send_save);
                serialport.Write(b_send_save, 0, 1);
            }
            int send_show = (usart_data | (0xC0));
            byte[] b_send_show = BitConverter.GetBytes(send_show);
            serialport.Write(b_send_show, 0, 1);
            Thread.Sleep(5); // ->> it would be needed to make sure ot work normally
            serialport.Dispose();


        }
        private void Show_White_Click(object sender, EventArgs e)
        {
            show_FullScreen_Color('W');
        }
        private void Show_Black_Click(object sender, EventArgs e)
        {
            show_FullScreen_Color('B');
        }
        private void Show_Red_Click(object sender, EventArgs e)
        {
            show_FullScreen_Color('r');
        }
        private void Show_Green_Click(object sender, EventArgs e)
        {
            show_FullScreen_Color('g');
        }
        private void Show_Blue_Click(object sender, EventArgs e)
        {
            show_FullScreen_Color('b');   
        }

        
    }
}
