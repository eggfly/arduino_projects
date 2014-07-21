using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;

namespace BadApple
{
    class Program
    {
        static void Main(string[] args)
        {
            string dirname = "C:\\The KMPlayer\\Capture\\";
            // string filename = "C:\\The KMPlayer\\Capture\\坏苹果.mkv0143.jpg";
            FileStream output = File.OpenWrite("data.bin");
            foreach (string file in Directory.EnumerateFiles(dirname))
            {
                System.Console.WriteLine(file);
                //Image image = Image.FromFile(filename);
                //Graphics g = Graphics.FromImage(image);
                Image origin = Bitmap.FromFile(file);
                Bitmap newBitmap = new Bitmap(origin, new Size(64, 42));
                // newBitmap.Save("output.bmp");
                byte[] data = new byte[newBitmap.Height * newBitmap.Width / 8];
                for (int y = 0; y < newBitmap.Height; y++)
                {
                    for (int x = 0; x < newBitmap.Width; x++)
                    {
                        int offset = newBitmap.Width / 8 * y + x / 8;
                        int bit = x % 8;
                        Color color = newBitmap.GetPixel(x, y);
                        int gray = (color.R + color.G + color.B) / 3;
                        byte pixel = (gray >= 128) ? (byte)1 : (byte)0;
                        data[offset] |= (byte)(pixel << (7 - bit));
                        if (bit == 7)
                        {
                     //       System.Console.Write(data[offset]);
                       //     System.Console.Write(",");
                        }
                        if (x == newBitmap.Width - 1)
                        {
                         //   System.Console.WriteLine();
                        }
                    }
                }
                output.Write(data, 0, data.Length);
            }
        }
    }
}
