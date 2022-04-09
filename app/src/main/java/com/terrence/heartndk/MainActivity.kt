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
    //lateinit var progressBar: ProgressBar
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Initializing the download helper with with appropriate timeouts
        val presets = PRDownloaderConfig.newBuilder()
            .setReadTimeout(30000)
            .setConnectTimeout(30000)
            .build()
        PRDownloader.initialize(applicationContext, presets)

        val url =
            "https://terrence-aluda.com/dataset/heart.csv"
        val fileName = "heart.csv"

       // download(url, fileName)

        //passing the directory of the downloaded file location
        binding.sampleText.text = testPrediction(getFilesDir().getAbsolutePath())

    }

    private fun download(url: String, fileName: String) {
        PRDownloader.download(
            url,
            filesDir.absolutePath,/*the path*/
            fileName /*the name*/
        )
            .build()
            .start(object : OnDownloadListener {
                override fun onDownloadComplete() {
                    Toast.makeText(baseContext, "done", Toast.LENGTH_SHORT)
                        .show()
                }

                override fun onError(error: com.downloader.Error?) {
                    Toast.makeText(baseContext, "Failed to download the file", Toast.LENGTH_SHORT)
                        .show()
                }
            })
    }

    /**
     * A native method that is implemented by the 'heartndk' native library,
     * which is packaged with this application.
     */
    external fun testPrediction(path: String): String

    companion object {
        // Used to load the 'heartndk' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}