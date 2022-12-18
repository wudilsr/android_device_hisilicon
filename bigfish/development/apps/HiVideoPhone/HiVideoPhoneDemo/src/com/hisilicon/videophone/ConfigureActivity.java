package com.hisilicon.videophone;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.util.Enumeration;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class ConfigureActivity extends Activity implements OnClickListener {

    private final String CONFIGURE_FILE = "configure_file";
    private final int DEFAULT_VIDEO_PORT = 30010;
    private final int DEFAULT_AUDIO_PORT = 30020;

    private Spinner editResolution;
    private Button btnStart;
    private TextView textLocalIp;

    private EditText editVideoPort;
    private EditText editAudioPort;
    private EditText editRemoteIP1;
    private EditText editRemoteIP2;
    private EditText editRemoteIP3;
    private EditText editRemoteIP4;

    private int resolution;
    private int videoPort;
    private int audioPort;
    private String localIP;
    private String remoteIP;
    private String editIP1;
    private String editIP2;
    private String editIP3;
    private String editIP4;
    private String[] resolutionArray;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.configure_view);
        initView();
        loadLocalSave();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.btn_start:
            if (configureFinish()) {
                SharedPreferences preferences = getSharedPreferences(CONFIGURE_FILE, MODE_PRIVATE);
                SharedPreferences.Editor editor = preferences.edit();
                editor.putInt("resolution", resolution);
                editor.putInt("videoPort", videoPort);
                editor.putInt("audioPort", audioPort);
                editor.putString("localIP", localIP);
                editor.commit();

                Intent intent = new Intent(ConfigureActivity.this,VideoPhoneActivity.class);
                intent.putExtra("resolution", resolution);
                intent.putExtra("videoPort", videoPort);
                intent.putExtra("audioPort", audioPort);
                intent.putExtra("remoteIP", remoteIP);
                intent.putExtra("localIP", localIP);
                startActivity(intent);
            } else {
                Toast.makeText(this, getString(R.string.prompt_message), Toast.LENGTH_SHORT).show();
            }
            break;

        default:
            break;
        }
    }

    private void initView() {
        resolutionArray = getResources().getStringArray(R.array.resolution_array);
        localIP = getIpAddress().trim();
        editIP1 = "";
        editIP2 = "";
        editIP3 = "";
        editIP4 = "";

        editResolution = (Spinner) findViewById(R.id.edit_resolution);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, resolutionArray);
        adapter.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        editResolution.setAdapter(adapter);

        textLocalIp = (TextView) findViewById(R.id.text_local_ip);
        btnStart = (Button) findViewById(R.id.btn_start);
        btnStart.setOnClickListener(this);

        editVideoPort = (EditText) findViewById(R.id.edit_video_port);
        editAudioPort = (EditText) findViewById(R.id.edit_audio_port);
        editRemoteIP1 = (EditText) findViewById(R.id.edit_remote_iP_1);
        editRemoteIP2 = (EditText) findViewById(R.id.edit_remote_iP_2);
        editRemoteIP3 = (EditText) findViewById(R.id.edit_remote_iP_3);
        editRemoteIP4 = (EditText) findViewById(R.id.edit_remote_iP_4);

        editRemoteIP4.requestFocus();
    }

    private void loadLocalSave() {
        SharedPreferences preferences = getSharedPreferences(CONFIGURE_FILE, MODE_PRIVATE);
        resolution = preferences.getInt("resolution", -1);
        videoPort = preferences.getInt("videoPort", -1);
        audioPort = preferences.getInt("audioPort", -1);

        if (-1 == resolution)
            resolution = resolutionArray.length - 1;
        if (-1 == videoPort)
            videoPort = DEFAULT_VIDEO_PORT;
        if (-1 == audioPort)
            audioPort = DEFAULT_AUDIO_PORT;
        if (!isEmpty(localIP)) {
            String[] editIPs = localIP.split("\\.");
            editIP1 = editIPs[0];
            editIP2 = editIPs[1];
            editIP3 = editIPs[2];
            textLocalIp.setText(localIP);
        }
        editResolution.setSelection(resolution);
        editVideoPort.setText(String.valueOf(videoPort));
        editAudioPort.setText(String.valueOf(audioPort));

        editRemoteIP1.setText(editIP1);
        editRemoteIP2.setText(editIP2);
        editRemoteIP3.setText(editIP3);
        editRemoteIP4.setText(editIP4);
    }

    private boolean configureFinish() {
        String editVideo = editVideoPort.getText().toString().trim();
        String editAudio = editAudioPort.getText().toString().trim();

        editIP1 = editRemoteIP1.getText().toString().trim();
        editIP2 = editRemoteIP2.getText().toString().trim();
        editIP3 = editRemoteIP3.getText().toString().trim();
        editIP4 = editRemoteIP4.getText().toString().trim();
        if (isEmpty(editVideo) || isEmpty(editAudio) || isEmpty(editIP1) || isEmpty(editIP2) || isEmpty(editIP3) || isEmpty(editIP4)) {
            return false;
        }

        StringBuffer sb = new StringBuffer();
        sb.append(editIP1).append(".").append(editIP2).append(".").append(editIP3).append(".").append(editIP4);
        remoteIP = sb.toString();
        resolution = editResolution.getSelectedItemPosition();
        videoPort = Integer.parseInt(editVideo);
        audioPort = Integer.parseInt(editAudio);
        return true;

    }

    private boolean isEmpty(String str) {
        return null == str || "".equals(str);
    }

    public String getIpAddress() {
        String ipaddress = "";
        Enumeration<NetworkInterface> netInterfaces = null;
        try {
            netInterfaces = NetworkInterface.getNetworkInterfaces();
            while (netInterfaces.hasMoreElements()) {
                NetworkInterface intf = netInterfaces.nextElement();
                if (intf.getName().equalsIgnoreCase("eth0") || intf.getName().equalsIgnoreCase("wlan0")) {
                    for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                        InetAddress inetAddress = enumIpAddr.nextElement();
                        if (!inetAddress.isLoopbackAddress()) {
                            ipaddress = inetAddress.getHostAddress().toString();
                        }
                    }
                } else {
                    continue;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return ipaddress;
    }

}