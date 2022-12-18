package com.discretix.drmactions;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.io.FileInputStream;

import android.content.Context;
import android.drm.DrmInfo;
import android.drm.DrmInfoRequest;
import android.drm.DrmManagerClient;
import android.os.StrictMode;
import android.os.StrictMode.ThreadPolicy;
import android.util.Log;

import com.discretix.drmactions.auxillary.Constants;
import com.discretix.drmactions.auxillary.Utilities;
import com.discretix.drmassist.DrmActionSync;

/**
 * Acquire rights for a encrypted file using file headers
 */
public class AcquireRightsByApp extends DrmActionSync {

       private static final String ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT_GUID = "79f049a40988642ab92e65be0885f95";

       private static final String ASF_CONTENT_PROTECTION_SYSTEM_MICROSOFT_PLAYREADY_GUID = "107063f4c33cd42b932b48adf3a6a54";
	/*
	 * (non-Javadoc)
	 * @see com.discretix.drmassist.DrmActionBase#getName()
	 */
	public String getName() {
		return "Acquire Rights by Application";
	}

	/*
	 * (non-Javadoc)
	 * @see com.discretix.drmassist.DrmActionBase#isSupported(java.lang.String, java.lang.String)
	 */
	public boolean isSupported(String extension, String filePath) {
		return Utilities.isPlayreadyDrm(extension);
	}

	/*
	 * (non-Javadoc)
	 * @see com.discretix.drmassist.DrmActionAsync#perform(android.content.Context, java.lang.String, java.lang.String)
	 */
	protected String perform(Context context, final String filePath, final String extension)
	{

		ThreadPolicy tp = ThreadPolicy.LAX;
		StrictMode.setThreadPolicy(tp);

		/*if (!filePath.toLowerCase().endsWith("superspeedway_720_230.ismv") && !filePath.toLowerCase().endsWith("bear_video_opls0.pyv") )
		{
			return ("File Not Supported for this operation");
		}*/

		DrmInfoRequest request = new DrmInfoRequest(DrmInfoRequest.TYPE_RIGHTS_ACQUISITION_INFO, Utilities.extension2mimeType(extension));
		DrmManagerClient drmClient = new DrmManagerClient(context);

		//prepare generate license challenge
		String PiffHeaderStr = "<WRMHEADER xmlns=\"http://schemas.microsoft.com/DRM/2007/03/PlayReadyHeader\" version=\"4.0.0.0\"><DATA><PROTECTINFO><KEYLEN>16</KEYLEN><ALGID>AESCTR</ALGID></PROTECTINFO><KID>AmfjCTOPbEOl3WD/5mcecA==</KID><CHECKSUM>BGw1aYZ1YXM=</CHECKSUM><CUSTOMATTRIBUTES><IIS_DRM_VERSION>7.1.1064.0</IIS_DRM_VERSION></CUSTOMATTRIBUTES><LA_URL>http://playready.directtaps.net/pr/svc/rightsmanager.asmx</LA_URL><DS_ID>AH+03juKbUGbHl1V/QIwRA==</DS_ID></DATA></WRMHEADER>";
		String PyvHeaderStr  = null;//"<WRMHEADER xmlns=\"http://schemas.microsoft.com/DRM/2007/03/PlayReadyHeader\" version=\"4.0.0.0\"><DATA><PROTECTINFO><KEYLEN>16</KEYLEN><ALGID>AESCTR</ALGID></PROTECTINFO><KID>tusYN3uoeU+zLAXCJuHQ0w==</KID><LA_URL>http://playready.directtaps.net/pr/svc/rightsmanager.asmx?contentid=tusYN3uoeU+zLAXCJuHQ0w==</LA_URL><DS_ID>AH+03juKbUGbHl1V/QIwRA==</DS_ID><CHECKSUM>3hNyF98QQko=</CHECKSUM></DATA></WRMHEADER>";

          DrmManagerClient drmClient_header = new DrmManagerClient(context);
	      DrmInfoRequest request_header = new DrmInfoRequest(DrmInfoRequest.TYPE_RIGHTS_ACQUISITION_INFO, Utilities.extension2mimeType(extension));
	      DrmInfo response_header;
	      String HeaderStr = null;

	      request_header.put(Constants.DRM_ACTION, Constants.DRM_ACTION_GET_DRM_HEADER);
	      //request_header.put(Constants.DRM_DATA, "/mnt/sdcard/app.ismc");
	      request_header.put(Constants.DRM_DATA, filePath);

	      // get header
	      response_header = drmClient_header.acquireDrmInfo(request_header);
	      drmClient_header.release();
	      if ( null == response_header || !response_header.get(Constants.DRM_STATUS).equals("ok") )
	      {
	         Log.e("test", "Get DRM Header Failed!");
	      }
	      HeaderStr = (String)response_header.get(Constants.DRM_DATA);
             /*if(filePath.toLowerCase().endsWith(".pyv") || filePath.toLowerCase().endsWith(".pya"))
             {
                try
                {
                    //InputStream input = new InputStream(new FileInputStream(filePath));
                    FileInputStream input = new FileInputStream(filePath);

                    int count = 0;
                    byte bufsize[] = new byte[100];

                    input.read(bufsize, 0, 16);

                    int numread = input.read(bufsize, 0, 8);

                    String size = "";

                    Log.i("AcquireRightsByApp", "Numread:" + numread);

                    for (int i = 0, j = numread - 1; i < numread; i++, j--)
                    {
                        //Log.i("AcquireRights", " " + Integer.toHexString(bufsize[i] & 0xff));
                        size += Integer.toHexString(bufsize[j] & 0xff);
                    }

                    int objectSize = Integer.valueOf(size, 16);
                    Log.i("AcquireRightsByApp", "Objectsize:" + objectSize);

                    input.read(bufsize, 0, 6);

                    byte buf[] = new byte[objectSize - 16 - 8 - 6];

                    input.read(buf, 0, objectSize - 16 - 8 - 6);

                    PyvHeaderStr = parseDrmHeaderObject(buf, objectSize - 16 - 8 - 6);

                    if(PyvHeaderStr == null)
                        return("FAILURE");
                    else
                        Log.i("AcquireRightsByApp", "PyvHeaderStr:" + PyvHeaderStr);
                }
                catch (MalformedURLException e)
                {
                    e.printStackTrace();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
             }*/

             //"<WRMHEADER xmlns=\"http://schemas.microsoft.com/DRM/2007/03/PlayReadyHeader\" version=\"4.0.0.0\"><DATA><PROTECTINFO><KEYLEN>16</KEYLEN><ALGID>AESCTR</ALGID></PROTECTINFO><KID>tusYN3uoeU+zLAXCJuHQ0w==</KID><LA_URL>http://playready.directtaps.net/pr/svc/rightsmanager.asmx?</LA_URL><LUI_URL>http://playready.directtaps.net/pr/svc/rightsmanager.asmx?</LUI_URL><DS_ID>AH+03juKbUGbHl1V/QIwRA==</DS_ID><CHECKSUM>3hNyF98QQko=</CHECKSUM></DATA></WRMHEADER>";
		request.put(Constants.DRM_ACTION, Constants.DRM_OP_CODE_RIGHTS_GENERATE_LIC_CHALLENGE);
		//request.put(Constants.DRM_HEADER, response.get(Constants.DRM_DATA));
/*
		if (filePath.toLowerCase().endsWith(".ismv"))
		{
			request.put(Constants.DRM_HEADER, PiffHeaderStr);
		}
		else if (filePath.toLowerCase().endsWith(".pyv"))
		{
			request.put(Constants.DRM_HEADER, PyvHeaderStr);
		}
		else if (filePath.toLowerCase().endsWith(".pya"))
		{
			request.put(Constants.DRM_HEADER, PyvHeaderStr);
		}
*/
		request.put(Constants.DRM_HEADER, HeaderStr);
		DrmInfo response = drmClient.acquireDrmInfo(request);

		if ( null == response || !response.get(Constants.DRM_STATUS).equals("ok") )
		{
			Log.e("AcquireRightsByApp", "DrmManagerClient::AcquireRightsByApp failed");
			return("FAILURE");
		}

		Log.i("AcquireRightsByApp", "acquireDrmInfo returned "+response.get(Constants.DRM_STATUS));

		String challenge = response.get(Constants.DRM_DATA).toString();
		String laUrl     = response.get(Constants.LA_URL).toString();

		if (laUrl.isEmpty() || challenge.isEmpty())
		{
			Log.e("AcquireRightsByApp", "DrmManagerClient::AcquireRightsByApp failed, laUrl or chanllenge are invalid");
			return("FAILURE");
		}

		// send to server
		Log.i("AcquireRightsByApp"," LA_URL = "+laUrl);


		try
		{
			URL obj;
			obj = new URL(laUrl);
			HttpURLConnection con = (HttpURLConnection) obj.openConnection();

			//add reuqest header
			con.setRequestMethod("POST");
			con.setRequestProperty("Content-Type", "text/xml; charset=utf-8");
			con.setRequestProperty("SOAPAction", "http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");

			// Send post request
			con.setDoOutput(true);
			DataOutputStream wr = new DataOutputStream(con.getOutputStream());
			wr.writeBytes(challenge);
			wr.flush();
			wr.close();

	             int responseCode = con.getResponseCode();
			System.out.println("\nSending 'POST' request to URL : " + laUrl);
			System.out.println("Response Code : " + responseCode);

			if (responseCode != 200)
			{
				return("Failure - server error "+ responseCode);
			}

			//process response
			BufferedReader in = new BufferedReader(
			        new InputStreamReader(con.getInputStream()));
			String inputLine;
			StringBuffer Httpresponse = new StringBuffer();

			while ((inputLine = in.readLine()) != null) {
				Httpresponse.append(inputLine);
			}
			in.close();
			con.disconnect();

                    //print result
			//System.out.println(Httpresponse.toString());
			request.put(Constants.DRM_ACTION, Constants.DRM_ACTION_PROCESS_LIC_RESPONSE);
			request.put(Constants.DRM_DATA, Httpresponse.toString());

			response = drmClient.acquireDrmInfo(request);

			if ( null == response || !response.get(Constants.DRM_STATUS).equals("ok") )
			{
				Log.e("AcquireRightsByApp", "DrmManagerClient::AcquireRightsByApp process license response failed");
				return("FAILURE");
			}

			//Log.i("AcquireRightsByApp", "acquireDrmInfo returned "+response.get(Constants.DRM_STATUS));

			// send Ack to server
			String ack = response.get(Constants.DRM_DATA).toString();

			if (ack.length() == 0)
			{
				return ("SUCCESS");
			}


			Log.i("AcquireRightsByApp", "acquireDrmInfo requires to send ack");
			HttpURLConnection con2 = (HttpURLConnection) obj.openConnection();

			//add reuqest header
			con2.setRequestMethod("POST");
			con2.setRequestProperty("Content-Type", "text/xml; charset=utf-8");
				// Send post request
			con2.setDoOutput(true);

			DataOutputStream wr2 = new DataOutputStream(con2.getOutputStream());
			wr2.writeBytes(ack);
			wr2.flush();
			wr2.close();

			responseCode = con2.getResponseCode();
			System.out.println("\nSending 'POST' request to URL : " + laUrl);
			System.out.println("Response Code : " + responseCode);

			if (responseCode != 200)
			{
				return("Failure - server error "+ responseCode);
			}

			//process response
			BufferedReader in2 = new BufferedReader(
			        new InputStreamReader(con2.getInputStream()));
			String inputLine2;
			StringBuffer Httpresponse2 = new StringBuffer();

			while ((inputLine2 = in2.readLine()) != null) {
				Httpresponse2.append(inputLine2);
			}
			in2.close();
			con2.disconnect();

			// process ack response
			request.put(Constants.DRM_ACTION, Constants.DRM_ACTION_PROCESS_LIC_ACK_RESPONSE);
			request.put(Constants.DRM_DATA, Httpresponse2.toString());

			response = drmClient.acquireDrmInfo(request);

			if ( null == response || !response.get(Constants.DRM_STATUS).equals("ok") )
			{
				Log.e("AcquireRightsByApp", "DrmManagerClient::AcquireRightsByApp process ack response failed");
				return("FAILURE");
			}

			Log.i("AcquireRightsByApp", "acquireDrmInfo returned "+response.get(Constants.DRM_STATUS));

		}
		catch (MalformedURLException e1)
		{
			e1.printStackTrace();
		}
		catch (IOException e1) {
			e1.printStackTrace();
		}
		return("SUCCESS");

	}
       private String parseDrmHeaderObject(byte buf[], int len)
       {
            int dataNum = len;
            int offset = 0;

            while (offset < dataNum)
            {
                byte bufID[] = new byte[16];
                System.arraycopy(buf, offset, bufID, 0, 16);
                int bufIDLength = bufID.length;
                String bufIDStr = "";

                Log.i("AcquireRightsByApp", "BufIDLength:" + bufIDLength);

                for (int i = 0; i < bufIDLength; i++)
                {
                    bufIDStr += Integer.toHexString(bufID[i] & 0xff);
                }

                byte bufSize[] = new byte[8];
                System.arraycopy(buf, offset + 16, bufSize, 0, 8);
                int bufSizeLength = bufSize.length;
                String bufSizeStr = "";

                for (int j = bufSizeLength - 1; j >= 0; j--)
                {
                    bufSizeStr += Integer.toHexString(bufSize[j] & 0xff);
                }

                int ObjectSize = Integer.valueOf(bufSizeStr, 16);

                Log.i("AcquireRightsByApp", "BufIDStr: " + bufIDStr);
                Log.i("AcquireRightsByApp", "Offset: " + offset + " Objectsize: " + ObjectSize);

                if (bufIDStr.equals(ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT_GUID))
                {
                    byte drmCheck[] = new byte[16];
                    System.arraycopy(buf, offset + 24, drmCheck, 0, 16);
                    int drmCheckLength = drmCheck.length;
                    String drmCheckStr = "";
                    for (int i = 0; i < drmCheckLength; i++)
                    {
                        drmCheckStr += Integer.toHexString(drmCheck[i] & 0xff);
                    }

                    Log.i("AcquireRightsByApp", "DrmCheckStr: " + drmCheckStr);
                    if (drmCheckStr.equals(ASF_CONTENT_PROTECTION_SYSTEM_MICROSOFT_PLAYREADY_GUID))
                    {
                        byte drmHeaderLength[] = new byte[2];
                        System.arraycopy(buf, offset + 56, drmHeaderLength, 0, 2);
                        String drmHeaderLengthStr = Integer.toHexString(drmHeaderLength[1]
                                                                    & 0xff)
                                                + Integer.toHexString(drmHeaderLength[0] & 0xff);
                        int drmHeaderSize = Integer.valueOf(drmHeaderLengthStr, 16);
                        Log.i("AcquireRightsByApp", "DrmHeaderSize: " + drmHeaderSize);
                        byte drmHeader[] = new byte[drmHeaderSize];
                        System.arraycopy(buf, offset + 58, drmHeader, 0, drmHeaderSize);
                        char drmHeaderResult[] = new char[drmHeaderSize / 2];
                        int i = 0;
                        for (int j = 0; j < drmHeader.length; i++, j += 2)
                        {
                            drmHeaderResult[i] = (char)(drmHeader[j] & 0xff);
                        }

                        String Result = String.valueOf(drmHeaderResult);
                        return Result;
                    }
                    else
                    {
                        Log.e("AcquireRightsByApp", "IT'S NOT MICROSOFT PLAYREADY PROTECTION SYSTEM!");
                    }
                    return null;
                }
                offset += ObjectSize;
            }
            return null;
        }
}
