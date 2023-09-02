# Ili9341-Stm32

ILI9341 is drived by stm32f303 discovery board. Here we use GPIO to simulate spi interface to control ili9341,
and default usart to send signal to stm32.

     usart            spi
PC --------> stm32 -------> Ili9341

UI has two function :
1. send signal to tell ili9341 show full screen pure color
2. loads *.png image and resizes to 320 x 240 pixel, then send image data to show on ili9341

note : stm32 doesn's has enought flash to store entire image data, here we use linkedlist to store and release data step by stpe

---------------------------------------------------------------------------------------------------------------------------------
# Ili9341-Stm32

使用 stm32f303 discovery board 來控制 Ili9341，這裡使用GPIO來模擬Spi協定來與ili9341溝通，
並使用stm32自帶的usart功能來與PC做溝通

     usart            spi
PC --------> stm32 -------> Ili9341

UI 目前有兩個功能:
1. 傳送訊號讓ili9341 顯示滿螢幕純色
2. 讀取 *png 圖片並重新調整大小到 320 * 240 ， 然後讓ili9341顯示該圖片

note : stm32本身裝不下整張圖的資料，因此這裡使用Linkedlist 分階段存下圖片像素資料並釋放資源。
