import java.io.DataOutputStream
import java.io.File
import javax.imageio.ImageIO


const val Threshold = 128

fun main(args: Array<String>) {
    if (args.size != 2) {
        println("Usage: binary-image-generator <input file> <output file>")
    }

    val input = File(args[0])
    val output = File(args[1])

    require(input.isFile, { "Input must be a file" })

    val img = ImageIO.read(input)

    println("Image size (${img.width}, ${img.height}), threshold $Threshold, converting...")

    DataOutputStream(output.outputStream()).use { w ->
        w.writeInt(img.width)
        w.writeInt(img.height)

        val bytes = img.getRGB(0, 0, img.width, img.height, null, 0, img.width)
            .map { raw ->
                val r = (raw shr 24) and 0xFF
                val g = (raw shr 16) and 0xFF
                val b = (raw shr 8) and 0xFF

                val avg = (r + g + b) / 3
                if (avg < Threshold) 0.toByte() else 1.toByte()
            }
            .toByteArray()
        w.write(bytes)
    }

    println("Binary file written to $output.")
}