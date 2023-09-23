# Ili9341-Stm32

In this project, we interface an ILI9341 display with an STM32F303 Discovery board. Instead of using default SPI communication, we use GPIO pins to simulate SPI communication to control the ILI9341 display. Additionally, we use the default USART interface to send signals to the STM32 board.
             
PC ----(usart )----> stm32 ---(spi)----> Ili9341

UI has three functions :
1. Displaying Solid Colors: We send signals to tell the ILI9341 display to show a full-screen solid color.
2. Image Display: We load *.png images, resize them to 320 x 240 pixels, and then transmit the image data to be displayed on the ILI9341.
3. seletion of gamma (gamma1.0, gamma2.2)

Managing Limited Flash Storage : 
It's important to note that the STM32 board doesn't have sufficient flash storage to store an entire image. To overcome this limitation, we implement a linked list data structure to efficiently manage and display partial segments of the image. Once a segment is displayed, we free up the memory, allowing us to sequentially display the entire image.

---------------------------------------------------------------------------------------------------------------------------------
# Ili9341-Stm32

使用 stm32f303 discovery board 來控制 Ili9341，這裡使用GPIO來模擬Spi協定來與ili9341溝通，
並使用stm32自帶的usart功能來與PC做溝通

PC ----(usart )----> stm32 ---(spi)----> Ili9341

UI 目前有三個功能:
1. 傳送訊號讓ili9341 顯示滿螢幕純色
2. 讀取 *png 圖片並重新調整大小到 320 * 240 ， 然後讓ili9341顯示該圖片
3. 切換兩組gamma電壓，可即時變換gamma曲線 (Gamma1.0, Gamma2.2)

note : stm32本身裝不下整張圖的資料，因此這裡使用Linkedlist，先儲存一小段圖片，顯示後清空list，然後重複以上動作以完成整張圖。
