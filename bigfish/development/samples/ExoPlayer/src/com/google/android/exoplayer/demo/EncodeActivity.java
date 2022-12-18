package com.google.android.exoplayer.demo;

import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;

import com.google.android.exoplayer.demo.EncodeDecodeTest.EncodeDecodeListener;

import android.app.ListActivity;
import android.content.ComponentName;
import android.content.Intent;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class EncodeActivity extends ListActivity {
    private static final String TAG = "EncodeActivity";

    private static final int TEST_ENCODE = 1;
    private static final int TEST_ENCODE_DONE = 2;
    private static final int TOAST_MESSAGE = 3;
    private static final int PROGRESS_CHANGE = 4;
    private static final int CODEC_NAME = 5;
    private static final int START_TIMER = 6;

    private EncodeDecodeTest mEncodeTest = new EncodeDecodeTest(this);
    private SystemUtils mSystemUtils = SystemUtils.getInstanse(this);
//    private Timer mCheckRateTimer = new Timer(true);

    private int averageCpuRateSum = 0;
    private int cpuReadCount = 0;

    private int averageVssSum = 0;
    private int vssReadCount = 0;

    private boolean testDone = false;

    private ListAdapterEncode mListAdapter = null;
    private String mCurrentResolution;
	
	public static String filePath = null;
	public static String fileNameYUV = null;
	public static String dirPath = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_encode);

        mListAdapter = new ListAdapterEncode(this);
        setListAdapter(mListAdapter);

        mEncodeTest.setOnEncodeDecodeListener(new OnEncodeDecodeListener());
		/*if (filePath.contains("720")) {
			startTest("720P");
		} else if (filePath.contains("1080")) {
			startTest("1080P");
		}*/
		startTest(mListAdapter.KeyResolutions[0]);

//        Message msgEncode = new Message();
//        msgEncode.what = START_TIMER;
//        myHandler.sendMessageDelayed(msgEncode, 500L);
//        mCheckRateTimer.schedule(new checkRateTask(), 500L);

		Log.d("zpp", "EncodeActivity filePath = "+filePath);

    }

    private class OnEncodeDecodeListener implements EncodeDecodeListener {
        @Override
        public void progressChange(int frames, String resolution) {
            //Log.d(TAG, "progressChange " + resolution + " " + frames);
            Message msg = new Message();
            msg.what = PROGRESS_CHANGE;
            msg.arg1 = frames;
            msg.obj = resolution;
            myHandler.sendMessage(msg);
        }

        @Override
        public void updateCodecName(String codecName) {
            Message msg = new Message();
            msg.what = CODEC_NAME;
            msg.obj = codecName;
            myHandler.sendMessage(msg);
        }

        @Override
        public void updateTotalTime(long delta, String resolution) {
            /*int frameRate = (int) (EncodeDecodeTest.NUM_FRAMES * 1000 / delta);
            long score = getScore(resolution, frameRate);
            mListAdapter.updateItem(resolution, "Score", score + "");
            mListAdapter.updateItem(resolution, "Rate", frameRate + "");
            mListAdapter.updateItem(resolution, "Time", delta + "");
            mListAdapter.updateItem(resolution, "Delay", EncodeDecodeTest.FirstFrameEncodedTime + "");*/

        }
    }

    private void startTest(String resolution) {
        drawStartEncode(resolution);

        mCurrentResolution = resolution;

        mListAdapter.resetColumn(resolution);

        Message msgEncode = new Message();
        msgEncode.what = TEST_ENCODE;
        msgEncode.obj = resolution;
        myHandler.sendMessageDelayed(msgEncode, 2000L);
    }

    private void drawStartEncode(String resolution) {
        for (int i = 0; i < mListAdapter.KeyResolutions.length; i++) {
            if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[i])) {
                int id = mListAdapter.ResolutionIds[i];
                String start_encode = String.format(getResources().getString(R.string.start_encode), resolution);
                TextView textView = (TextView) findViewById(id);
                textView.setText(start_encode);



                break;
            }
        }
    }

    private void drawFinishEncode(String resolution, boolean hasError) {
        for (int i = 0; i < mListAdapter.KeyResolutions.length; i++) {
            if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[i])) {
                String prompt = "";
                if (hasError) {
                    prompt = String.format(getResources().getString(R.string.encode_error), resolution);
                } else {
                    prompt = String.format(getResources().getString(R.string.finish_encode), resolution);
                }

                int id = mListAdapter.ResolutionIds[i];
                TextView textView = (TextView) findViewById(id);
                textView.setText(prompt);

                if(false == hasError) {
                    Button button = null;
					/*if (0 == i) {
						button = (Button)findViewById(R.id.button_play_qcif);
						button.setOnClickListener(new OnClickListener() {
							@Override
							public void onClick(View arg0) {
								Intent intent = new Intent();
								int width = 176;
								int height = 144;

								String fileName = "file://" + mEncodeTest.DEBUG_FILE_NAME_BASE + width + "x" + height + ".mp4";
								Uri uri = Uri.parse(fileName);
								ComponentName comp = new ComponentName("android", "com.android.internal.app.ResolverActivity");

								intent.setAction("android.intent.action.VIEW");
								intent.setDataAndType(uri, "video/*");
								intent.setComponent(comp);
								startActivity(intent);
								
								//overridePendingTransition(R.anim.in_from_right, R.anim.out_to_left); 
							}
							
						});
					}
					else if (1 == i) {
						button = (Button)findViewById(R.id.button_play_d1);
						button.setOnClickListener(new OnClickListener() {
							@Override
							public void onClick(View arg0) {
								Intent intent = new Intent();
								int width = 720;
								int height = 480;

								String fileName = "file://" + mEncodeTest.DEBUG_FILE_NAME_BASE + width + "x" + height + ".mp4";
								Uri uri = Uri.parse(fileName);
								ComponentName comp = new ComponentName("android", "com.android.internal.app.ResolverActivity");

								intent.setAction("android.intent.action.VIEW");
								intent.setDataAndType(uri, "video/*");
								intent.setComponent(comp);
								startActivity(intent);
								
								//overridePendingTransition(R.anim.in_from_right, R.anim.out_to_left); 
							}
							
						});
					}
					else*/ if (2 == i) {
                        button = (Button)findViewById(R.id.button_play_720p);
                        button.setOnClickListener(new OnClickListener() {
                            @Override
                            public void onClick(View arg0) {
                                Intent intent = new Intent();
                                int width = 1280;
                                int height = 720;

                                String fileName = "file://" + mEncodeTest.DEBUG_FILE_NAME_BASE + width + "x" + height + ".mp4";
                                Uri uri = Uri.parse(fileName);
                                ComponentName comp = new ComponentName("android", "com.android.internal.app.ResolverActivity");

                                intent.setAction("android.intent.action.VIEW");
                                intent.setDataAndType(uri, "video/*");
                                intent.setComponent(comp);
                                startActivity(intent);

                                //overridePendingTransition(R.anim.in_from_right, R.anim.out_to_left);
                            }

                        });
                    }
                    else if (3 == i) {
                        button = (Button)findViewById(R.id.button_play_1080p);
                        button.setOnClickListener(new OnClickListener() {
                            @Override
                            public void onClick(View arg0) {
                                Intent intent = new Intent();
                                int width = 1920;
                                int height = 1080;

                                String fileName = "file://" + mEncodeTest.DEBUG_FILE_NAME_BASE + width + "x" + height + ".mp4";
                                Uri uri = Uri.parse(fileName);
                                ComponentName comp = new ComponentName("android", "com.android.internal.app.ResolverActivity");

                                intent.setAction("android.intent.action.VIEW");
                                intent.setDataAndType(uri, "video/*");
                                intent.setComponent(comp);
                                startActivity(intent);

                                //overridePendingTransition(R.anim.in_from_right, R.anim.out_to_left);
                            }

                        });
                    }

                    //button.setVisibility(1);
                }

                break;
            }
        }
    }


    private void updateEncodeProgress(int frames, String resolution) {
        //mListAdapter.updateItem(resolution, "Frames", frames + "");
        //mListAdapter.notifyDataSetChanged();
    }

    private Handler myHandler = new Handler() {
        public void handleMessage(Message msg) {
            if (msg.what == PROGRESS_CHANGE) {
                updateEncodeProgress(msg.arg1, (String) msg.obj);
            } else if (msg.what == TEST_ENCODE) {
                String resolution = (String) msg.obj;
                testEncode(resolution);
            } else if (msg.what == TEST_ENCODE_DONE) {
                mListAdapter.notifyDataSetChanged();

                String resolution = (String) msg.obj;
                drawFinishEncode(resolution, msg.arg1 == 1 ? true : false);

                String next = null;
                int i = 0;
                for (i = 0; i < mListAdapter.KeyResolutions.length - 1; i++) {
                    if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[i])) {
                        next = mListAdapter.KeyResolutions[i + 1];
                        break;
                    }
                }

                if (i >= mListAdapter.KeyResolutions.length - 1) {
                    Toast.makeText(getApplicationContext(), "Test done.", Toast.LENGTH_LONG).show();
                    OnTestDone();
                }

                if (next != null) {
                    startTest(next);
                }
            } else if (msg.what == TOAST_MESSAGE) {
                String string = (String) msg.obj;
                Toast.makeText(getApplicationContext(), string, Toast.LENGTH_LONG).show();
            } else if (msg.what == CODEC_NAME) {
                String codecName = String.format(getResources().getString(R.string.codec_name), msg.obj);
                TextView textView = (TextView) findViewById(R.id.textCodecName);
                textView.setText(codecName);
            } else if (msg.what == START_TIMER) {
                if (!testDone) {
//                    Log.d(TAG, "START_TIMER ");
                    //CheckRateTask();
                }
            }
        }
    };

    private long getScore(String resolution, int frameRate) {
        if (frameRate == 0) {
            return 0;
        }

        int w = 0, h = 0;
		/*if (resolution.equalsIgnoreCase("QCIF")) {
			w = 176;
			h = 144;
		} else if (resolution.equalsIgnoreCase("D1")) {
			w = 720;
			h = 480;
		} else*/ if (resolution.equalsIgnoreCase("720p")) {
            w = 1280;
            h = 720;
        } else if (resolution.equalsIgnoreCase("1080p")) {
            w = 1920;
            h = 1080;
        }

        return w * h * frameRate / 10000;
    }

    private void testEncode(final String resolution) {
        averageCpuRateSum = 0;
        cpuReadCount = 0;

        averageVssSum = 0;
        vssReadCount = 0;

        testDone = false;

        //CheckRateTask();

        Runnable runnable = new Runnable() {
            public void run() {
                boolean hasError = false;
//                long startTime = System.currentTimeMillis();

				try {
					/*if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[0])) {
						mEncodeTest.getYUVFramesByDecode(R.raw.mediatestqcif, EncodeDecodeTest.RESET_MODE_NONE, -1 , 176, 144);
						mEncodeTest.getYUVFramesFromFile(R.raw.testqcif, 176, 144);
						mEncodeTest.testEncodeDecodeVideoFromBufferToBufferQCIF();
					} else if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[1])) {
						mEncodeTest.getYUVFramesFromFile(R.raw.testd1, 720, 480);
						mEncodeTest.testEncodeDecodeVideoFromBufferToBufferD1();
					} else if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[2])) {
						mEncodeTest.testEncodeDecodeVideoFromBufferToBuffer720p();
					} else if (resolution.equalsIgnoreCase(mListAdapter.KeyResolutions[3])) {
					    mEncodeTest.testEncodeDecodeVideoFromBufferToBuffer1080p();
					} else {
						Log.e(TAG, "Not support encode test resolution: " + resolution);
						return;
					}*/
					if (filePath.contains("720")) {
						mEncodeTest.testEncodeDecodeVideoFromBufferToBuffer720p();
					} else if(filePath.contains("1080")) {
						mEncodeTest.testEncodeDecodeVideoFromBufferToBuffer1080p();
                    }
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                     Log.e(TAG, "Create codec error: " + e.getMessage());
                     e.printStackTrace();
                     hasError = true;
                }

                testDone = true;
/*
                long endTime = System.currentTimeMillis();
                long delta = endTime - startTime;

                int frameRate = 0;
                if (hasError) {
                    delta = 0;
                    EncodeDecodeTest.FirstFrameEncodedTime = 0;
                } else {
                    frameRate = (int) (EncodeDecodeTest.NUM_FRAMES * 1000 / delta);
                }

                long score = getScore(resolution, frameRate);
                mListAdapter.updateItem(resolution, "Score", score + "");
                mListAdapter.updateItem(resolution, "Rate", frameRate + "");
                mListAdapter.updateItem(resolution, "Time", delta + "");
                mListAdapter.updateItem(resolution, "Delay", EncodeDecodeTest.FirstFrameEncodedTime + "");
*/
                if (hasError) {
                    cpuReadCount = 0;
                    vssReadCount = 0;
                }

                int averageCpuRate = 0;
                if (cpuReadCount > 0) {
                    //Log.e(TAG, "averageCpuRateSum: " + averageCpuRateSum + " cpuReadCount: " + cpuReadCount);
                    averageCpuRate = (int)((float)averageCpuRateSum / (float)cpuReadCount + 0.5);
                }
                mListAdapter.updateItem(resolution, "CPU", averageCpuRate + " %");

                int averageVss = 0;
                if (vssReadCount > 0) {
                    averageVss = (int)((float)averageVssSum / (float)vssReadCount + 0.5);
                }
                mListAdapter.updateItem(resolution, "Memory", averageVss / 1024 + " MB");

                Message msg = new Message();
                msg.what = TEST_ENCODE_DONE;
                if (hasError) {
                    msg.arg1 = 1;
                } else {
                    msg.arg1 = 0;
                }
                msg.obj = resolution;
                myHandler.sendMessage(msg);
            }
        };
        new Thread(runnable).start();
    }

    private void OnTestDone() {
        Log.e(TAG, "Test done.");
        testDone = true;
//        mCheckRateTimer.cancel();
    }

    public static int strToInt(String value, int defaultValue) {
        try {
            return Integer.parseInt(value);
        } catch (Exception e) {
            return defaultValue;
        }
    }
/*
    class checkRateTask extends TimerTask {
        @Override
        public void run() {
            HashMap<String, Integer> infos = mSystemUtils.getTopInfo();
            if (testDone) {
                return;
            }

            int cpuRate = infos.get("cpu");
            int memory = infos.get("rss");

            Log.d(TAG, "CPU rate: " + cpuRate + "% Memory: " + memory + "K");

            if (cpuRate > 0) {
                averageCpuRateSum += cpuRate;
                cpuReadCount++;
                mListAdapter.updateItem(mCurrentResolution, "CPU", cpuRate + " %");
            }

            if (memory > 0) {
                averageVssSum += memory;
                vssReadCount++;
                mListAdapter.updateItem(mCurrentResolution, "Memory", memory / 1024 + " MB");
            }

//            mCheckRateTimer.cancel();

            //Message msg = new Message();
            //msg.what = START_TIMER;
            //myHandler.sendMessage(msg);
        }
    };*/

    private void CheckRateTask() {
        Runnable runnable = new Runnable() {
            public void run() {
                HashMap<String, Integer> infos = mSystemUtils.getTopInfo();
                int cpuRate = infos.get("cpu");
                int memory = infos.get("rss");
                if (testDone) {
                    Log.d(TAG, "testDone over. ");
                    cpuRate = 0;
                    memory = 0;
                    //return;
                }


                Log.d(TAG, "CPU rate: " + cpuRate + "% Memory: " + memory + "K");

                if (cpuRate > 0) {
                    averageCpuRateSum += cpuRate;
                    cpuReadCount++;
                    mListAdapter.updateItem(mCurrentResolution, "CPU", cpuRate + " %");
                }

                if (memory > 0) {
                    averageVssSum += memory;
                    vssReadCount++;
                    mListAdapter.updateItem(mCurrentResolution, "Memory", memory / 1024 + " MB");
                }

                long delay = 300L;
                if (mCurrentResolution.equalsIgnoreCase("720P")) {
                    delay = 600L;
                } else if (mCurrentResolution.equalsIgnoreCase("1080P")) {
                    delay = 1200L;
                }
                Message msgEncode = new Message();
                msgEncode.what = START_TIMER;
                myHandler.sendMessageDelayed(msgEncode, delay);
            }
        };
        new Thread(runnable).start();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        OnTestDone();
        myHandler.removeMessages(TEST_ENCODE);
        myHandler.removeMessages(TEST_ENCODE_DONE);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
            Log.d(TAG, "KeyEvent.KEYCODE_BACK");

            finish();
            //overridePendingTransition(R.anim.in_from_left, R.anim.out_to_right);

            return true;
        }

        return super.onKeyDown(keyCode, event);
    }
}
