﻿namespace MasterUI
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置受控資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.Load = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.Send = new System.Windows.Forms.Button();
            this.Show_Red = new System.Windows.Forms.Button();
            this.Show_White = new System.Windows.Forms.Button();
            this.Show_Black = new System.Windows.Forms.Button();
            this.Show_Green = new System.Windows.Forms.Button();
            this.Show_Blue = new System.Windows.Forms.Button();
            this.Image = new System.Windows.Forms.Label();
            this.Screen = new System.Windows.Forms.Label();
            this.Gamma = new System.Windows.Forms.Label();
            this.gamma1 = new System.Windows.Forms.Button();
            this.gamma2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // Load
            // 
            this.Load.Location = new System.Drawing.Point(114, 37);
            this.Load.Name = "Load";
            this.Load.Size = new System.Drawing.Size(97, 42);
            this.Load.TabIndex = 0;
            this.Load.Text = "Load";
            this.Load.UseVisualStyleBackColor = true;
            this.Load.Click += new System.EventHandler(this.Load_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Location = new System.Drawing.Point(399, 13);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(427, 426);
            this.pictureBox2.TabIndex = 2;
            this.pictureBox2.TabStop = false;
            this.pictureBox2.Click += new System.EventHandler(this.pictureBox2_Click);
            // 
            // Send
            // 
            this.Send.Location = new System.Drawing.Point(233, 37);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(97, 42);
            this.Send.TabIndex = 3;
            this.Send.Text = "Send";
            this.Send.UseVisualStyleBackColor = true;
            this.Send.Click += new System.EventHandler(this.Send_Click);
            // 
            // Show_Red
            // 
            this.Show_Red.Location = new System.Drawing.Point(114, 107);
            this.Show_Red.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Show_Red.Name = "Show_Red";
            this.Show_Red.Size = new System.Drawing.Size(97, 22);
            this.Show_Red.TabIndex = 4;
            this.Show_Red.Text = "Show Red";
            this.Show_Red.UseVisualStyleBackColor = true;
            this.Show_Red.Click += new System.EventHandler(this.Show_Red_Click);
            // 
            // Show_White
            // 
            this.Show_White.Location = new System.Drawing.Point(233, 107);
            this.Show_White.Name = "Show_White";
            this.Show_White.Size = new System.Drawing.Size(97, 22);
            this.Show_White.TabIndex = 5;
            this.Show_White.Text = "Show White";
            this.Show_White.UseVisualStyleBackColor = true;
            this.Show_White.Click += new System.EventHandler(this.Show_White_Click);
            // 
            // Show_Black
            // 
            this.Show_Black.Location = new System.Drawing.Point(233, 135);
            this.Show_Black.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Show_Black.Name = "Show_Black";
            this.Show_Black.Size = new System.Drawing.Size(97, 24);
            this.Show_Black.TabIndex = 6;
            this.Show_Black.Text = "Show Black";
            this.Show_Black.UseVisualStyleBackColor = true;
            this.Show_Black.Click += new System.EventHandler(this.Show_Black_Click);
            // 
            // Show_Green
            // 
            this.Show_Green.Location = new System.Drawing.Point(114, 136);
            this.Show_Green.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Show_Green.Name = "Show_Green";
            this.Show_Green.Size = new System.Drawing.Size(97, 23);
            this.Show_Green.TabIndex = 7;
            this.Show_Green.Text = "Show Green";
            this.Show_Green.UseVisualStyleBackColor = true;
            this.Show_Green.Click += new System.EventHandler(this.Show_Green_Click);
            // 
            // Show_Blue
            // 
            this.Show_Blue.Location = new System.Drawing.Point(114, 164);
            this.Show_Blue.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Show_Blue.Name = "Show_Blue";
            this.Show_Blue.Size = new System.Drawing.Size(97, 22);
            this.Show_Blue.TabIndex = 8;
            this.Show_Blue.Text = "Show Blue";
            this.Show_Blue.UseVisualStyleBackColor = true;
            this.Show_Blue.Click += new System.EventHandler(this.Show_Blue_Click);
            // 
            // Image
            // 
            this.Image.AutoSize = true;
            this.Image.Location = new System.Drawing.Point(25, 50);
            this.Image.Name = "Image";
            this.Image.Size = new System.Drawing.Size(42, 15);
            this.Image.TabIndex = 9;
            this.Image.Text = "Image";
            // 
            // Screen
            // 
            this.Screen.AutoSize = true;
            this.Screen.Location = new System.Drawing.Point(28, 113);
            this.Screen.Name = "Screen";
            this.Screen.Size = new System.Drawing.Size(45, 15);
            this.Screen.TabIndex = 10;
            this.Screen.Text = "Screen";
            // 
            // Gamma
            // 
            this.Gamma.AutoSize = true;
            this.Gamma.Location = new System.Drawing.Point(32, 217);
            this.Gamma.Name = "Gamma";
            this.Gamma.Size = new System.Drawing.Size(51, 15);
            this.Gamma.TabIndex = 11;
            this.Gamma.Text = "Gamma";
            // 
            // gamma1
            // 
            this.gamma1.Location = new System.Drawing.Point(114, 217);
            this.gamma1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.gamma1.Name = "gamma1";
            this.gamma1.Size = new System.Drawing.Size(97, 22);
            this.gamma1.TabIndex = 12;
            this.gamma1.Text = "Gamma1.0";
            this.gamma1.UseVisualStyleBackColor = true;
            this.gamma1.Click += new System.EventHandler(this.gamma1_Click);
            // 
            // gamma2
            // 
            this.gamma2.Location = new System.Drawing.Point(233, 217);
            this.gamma2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.gamma2.Name = "gamma2";
            this.gamma2.Size = new System.Drawing.Size(97, 22);
            this.gamma2.TabIndex = 13;
            this.gamma2.Text = "Gamma2.2";
            this.gamma2.UseVisualStyleBackColor = true;
            this.gamma2.Click += new System.EventHandler(this.gamma2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(858, 450);
            this.Controls.Add(this.gamma2);
            this.Controls.Add(this.gamma1);
            this.Controls.Add(this.Gamma);
            this.Controls.Add(this.Screen);
            this.Controls.Add(this.Image);
            this.Controls.Add(this.Show_Blue);
            this.Controls.Add(this.Show_Green);
            this.Controls.Add(this.Show_Black);
            this.Controls.Add(this.Show_White);
            this.Controls.Add(this.Show_Red);
            this.Controls.Add(this.Send);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.Load);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Load;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Button Send;
        private System.Windows.Forms.Button Show_Red;
        private System.Windows.Forms.Button Show_White;
        private System.Windows.Forms.Button Show_Black;
        private System.Windows.Forms.Button Show_Green;
        private System.Windows.Forms.Button Show_Blue;
        private System.Windows.Forms.Label Image;
        private System.Windows.Forms.Label Screen;
        private System.Windows.Forms.Label Gamma;
        private System.Windows.Forms.Button gamma1;
        private System.Windows.Forms.Button gamma2;
    }
}

