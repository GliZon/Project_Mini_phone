from PIL import Image

img = Image.open("RST.png")

img = img.resize((80, 80))

img = img.convert("RGB")

with open("splash.raw", "wb") as f:

    for y in range(80):
        for x in range(80):

            r, g, b = img.getpixel((x, y))

            rgb565 = (
                ((r & 0xF8) << 8) |
                ((g & 0xFC) << 3) |
                (b >> 3)
            )

            # byte swap for ST7735
            rgb565 = (
                ((rgb565 & 0xFF) << 8) |
                (rgb565 >> 8)
            )

            f.write(rgb565.to_bytes(2, "big"))
