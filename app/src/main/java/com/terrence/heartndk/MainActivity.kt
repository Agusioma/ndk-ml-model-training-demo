package com.terrence.heartndk

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.ProgressBar
import android.widget.TextView
import android.widget.Toast
import com.downloader.OnDownloadListener
import com.downloader.PRDownloader
import com.downloader.PRDownloaderConfig
import com.terrence.heartndk.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    lateinit var btnDownload: Button
    lateinit var progressBar: ProgressBar
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        //btnDownload = binding.btnDownload
        progressBar = binding.progressBar
        // Example of a call to a native method
       // binding.sampleText.text = stringFromJNI()

        // Initialize PRDownloader with read and connection timeout
        val config = PRDownloaderConfig.newBuilder()
            .setReadTimeout(30000)
            .setConnectTimeout(30000)
            .build()
        PRDownloader.initialize(applicationContext, config)

        //val array2: Array<Double> = arrayOf(57.0,0.0,0.0,140.0,241.0,0.0,1.0,123.0,1.0,0.2,1.0,0.0,3.0)
        binding.sampleText.text = testArr(getFilesDir().getAbsolutePath())
        //var myArray2 = arrayOf<Int>(1,10,4,6,15)


        /*Toast.makeText(baseContext, pathFromJNI(getFilesDir().getAbsolutePath()), Toast.LENGTH_SHORT)
            .show()*/
       /* btnDownload.setOnClickListener {
            val url =
                "https://terrence-aluda.com/dataset/heart.csv"
            val fileName = "heart.csv"

            download(url, fileName)
        } */

    }

    private fun download(url: String, fileName: String) {
        PRDownloader.download(
            url,
            filesDir.absolutePath,
            fileName
        )
            .build()
            .setOnProgressListener {
                // Update the progress
                progressBar.max = it.totalBytes.toInt()
                progressBar.progress = it.currentBytes.toInt()
            }
            .start(object : OnDownloadListener {
                override fun onDownloadComplete() {
                    // Update the progress bar to show the completeness
                    progressBar.max = 100
                    progressBar.progress = 100

                    // Read the file
                    //readFile(fileName)
                    Toast.makeText(baseContext, "done", Toast.LENGTH_SHORT)
                        .show()
                }

                override fun onError(error: com.downloader.Error?) {
                    Toast.makeText(baseContext, "Failed to download the $url", Toast.LENGTH_SHORT)
                        .show()
                }

            })
    }

    /**
     * A native method that is implemented by the 'heartndk' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun testArr(path: String): String
    external fun pathFromJNI(path: String): String

    companion object {
        // Used to load the 'heartndk' library on application startup.
        init {
            System.loadLibrary("heartndk")
        }
    }
}