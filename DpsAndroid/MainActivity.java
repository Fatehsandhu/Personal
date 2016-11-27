package com.example.fssandhu.myapplication;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;

public class MainActivity extends AppCompatActivity {


    //URL to get Json weather
    private static String url = "http://api.openweathermap.org/data/2.5/weather?q=London,uk&appid=3ec44456254286753e8a540ba84a43b1";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new getWeather().execute();
    }

    private class getWeather extends AsyncTask<Void , Void , Void>{
        @Override
        protected void onPreExecute(){
            super.onPreExecute();
        }

        @Override
        protected Void doInBackground(Void... voids) {
            String jsonString = new HttpHandler().makeCall(url);
            Log.e("inbackground", "Response from url: " + jsonString);

            if (jsonString != null) {
                try {
                    JSONObject jsonObj = new JSONObject(jsonString);
                    JSONObject weather = jsonObj.getJSONObject("main");
                    String temp = weather.getString("temp");
                    System.out.println(temp);

                    System.out.println("Executing everything!");


                } catch (final JSONException e) {
                    Log.e("inbackground", "Json parsing error: " + e.getMessage());
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(getApplicationContext(),
                                    "Json parsing error: " + e.getMessage(),
                                    Toast.LENGTH_LONG)
                                    .show();
                        }
                    });

                }
            } else {
                Log.e("inbackground", "Couldn't get json from server.");
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(getApplicationContext(),
                                "Couldn't get json from server. Check LogCat for possible errors!",
                                Toast.LENGTH_LONG)
                                .show();
                    }
                });

            }

            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            super.onPostExecute(aVoid);
        }
    }
}
