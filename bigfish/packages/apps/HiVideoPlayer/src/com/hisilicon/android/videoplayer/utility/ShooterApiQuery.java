package com.hisilicon.android.videoplayer.utility;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;


/**
 * Query subtitle information according to file hash and file name
 * @author tobyPan
 *
 */
public class ShooterApiQuery {
	private static final String TAG = "ShooterApiQuery";
	private SearchResultListener mSearchResultListener = null;

	public ShooterApiQuery(SearchResultListener ls){
		mSearchResultListener = ls;
	}

	public void querySubTitie(String fileHash, String path){
		new SubtitleQueryThread(fileHash, path).start();
	}

	private class SubtitleQueryThread extends Thread{
		private String fileHash = "";
		private String path = "";
		private ArrayList<ShooterSubinfo> subList = new ArrayList<ShooterSubinfo>();

		SubtitleQueryThread(String fileHash, String path){
			this.fileHash = fileHash;
			this.path = path;
		}

		private void parseJson(String str){
			try
                    {
				JSONArray subTitleArray = new JSONArray(str);
				for(int i = 0; i < subTitleArray.length(); i++){
					ShooterSubinfo subtitleInfo = new ShooterSubinfo();
					JSONObject subObject = subTitleArray.getJSONObject(i);
					if(subObject.has("Desc")){
						subtitleInfo.setDesctribe(subObject.getString("Desc"));
					}

					if(subObject.has("Delay")){
						subtitleInfo.setDelay(subObject.getInt("Delay"));
					}

					JSONArray fileArray = subObject.getJSONArray("Files");
					for(int j = 0; j < fileArray.length(); j++){
						JSONObject fileObject = fileArray.getJSONObject(j);
						String ext = fileObject.getString("Ext");
						if(ext.equalsIgnoreCase("srt")){
							subtitleInfo.setExt("srt");
						}
						String link = fileObject.getString("Link");
						subtitleInfo.addFile(ext, link);
					}
					subtitleInfo.setFileHash(fileHash);
					Log.d(TAG, "subtitleInfo " + i + " :"+ subtitleInfo);

					if(subtitleInfo.getExt() != null)
						subList.add(subtitleInfo);
				}
			}
                    catch (JSONException e)
                    {
				Log.e(TAG, "error on parse Json " + e.toString());
				e.printStackTrace();
			}
		}

		/**
		 * Trust every server - don't check for any certificate
		 */
		private void trustAllHosts() {
			final String TAG = "trustAllHosts";
			// Create a trust manager that does not validate certificate chains
			TrustManager[] trustAllCerts = new TrustManager[] { new X509TrustManager() {

				public java.security.cert.X509Certificate[] getAcceptedIssuers() {
					return new java.security.cert.X509Certificate[] {};
				}

				public void checkClientTrusted(X509Certificate[] chain, String authType) throws CertificateException {
					Log.i(TAG, "checkClientTrusted");
				}

				public void checkServerTrusted(X509Certificate[] chain, String authType) throws CertificateException {
					Log.i(TAG, "checkServerTrusted");
				}
			} };

			// Install the all-trusting trust manager
			try {
				SSLContext sc = SSLContext.getInstance("TLS");
				sc.init(null, trustAllCerts, new java.security.SecureRandom());
				HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		@Override
		public void run() {
			String urlstr = "https://www.shooter.cn/api/subapi.php?";
			try {
				String hashEncoded = URLEncoder.encode(fileHash, "UTF-8");
				String pathinfoEncoded = URLEncoder.encode(path, "UTF-8");
				String formatEncoded = URLEncoder.encode("json", "UTF-8");
				String langEncoded = URLEncoder.encode("Chn", "UTF-8");
				urlstr = urlstr + "filehash=" + hashEncoded + "&pathinfo=" + pathinfoEncoded + "&format=" + formatEncoded + "&lang=" + langEncoded;
			} catch (UnsupportedEncodingException e) {
				Log.w(TAG, e.toString());
				e.printStackTrace();
			} catch (Exception e) {
				Log.w(TAG, e.toString());
				e.printStackTrace();
			}
			Log.d(TAG, "Shooter url: " + urlstr);
			HttpURLConnection connection = null;
			InputStream is = null;
			try {
				trustAllHosts();
				URL url = new URL(urlstr);
				connection = (HttpURLConnection) url.openConnection();
				connection.setConnectTimeout(2000);
				connection.setRequestMethod("POST");

				is = connection.getInputStream();
				BufferedReader br = new BufferedReader(new InputStreamReader(is));

				StringBuilder builder = new StringBuilder();
				String strline = null;
				while((strline = br.readLine()) != null){
					Log.d(TAG, strline);
					builder.append(strline + "/r/n");
				}
                           Log.i(TAG,"builder.toString():"+builder.toString());
				parseJson(builder.toString());
			} catch (Exception e) {
				Log.w(TAG, e.toString());
				e.printStackTrace();
			} finally {
				try
                           {
					mSearchResultListener.onSearchResult(path, subList);
                                  if(is != null)
					    is.close();
					connection.disconnect();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
	}

	public static interface SearchResultListener{
		void onSearchResult(String path, ArrayList<ShooterSubinfo> sublist);
	}
}
