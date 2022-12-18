/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.google.android.exoplayer.demo;

import com.google.android.exoplayer.demo.Samples.Sample;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ExpandableListView;
import android.widget.ExpandableListView.OnChildClickListener;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * An activity for selecting from a number of samples.
 */
public class SampleChooserActivity extends Activity {

  private boolean mBrowserFiles = false;

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.sample_chooser_activity);

    CheckBox disableAudio = (CheckBox) findViewById(R.id.disable_audio);
    if (UserInfo.getDiableAudio(this)) {
        disableAudio.setChecked(true);
    }
    disableAudio.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setDiableAudio(SampleChooserActivity.this, isChecked);
        }
    });

    CheckBox resizeWindow = (CheckBox) findViewById(R.id.resize_window);
    if (UserInfo.getResizeWindow(this)) {
        resizeWindow.setChecked(true);
    }
    resizeWindow.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setResizeWindow(SampleChooserActivity.this, isChecked);
        }
    });

    CheckBox tunneledPlayback = (CheckBox)findViewById(R.id.tunneled_playback);
    if (UserInfo.getTunneledPlayback(this)) {
        tunneledPlayback.setChecked(true);
    }
    tunneledPlayback.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView,
            boolean isChecked) {
            UserInfo.setTunneledPlayback(SampleChooserActivity.this, isChecked);
            if (isChecked) {
                if (UserInfo.getOverlay()) {
                    CheckBox overlay = (CheckBox) findViewById(R.id.overlay);
                    overlay.setChecked(false);
                }
                if (UserInfo.getSoftwareCodec(SampleChooserActivity.this)) {
                    CheckBox softwareCodec = (CheckBox) findViewById(R.id.software_codec);
                    softwareCodec.setChecked(false);
                }
            }
        }
    });

    CheckBox securePlayback = (CheckBox) findViewById(R.id.secure_playback);
    if (!UserInfo.isTrustedVideoPath()) {
        securePlayback.setVisibility(View.GONE);
        UserInfo.setSecurePlayback(SampleChooserActivity.this, false);
    }
    if (UserInfo.getSecurePlayback(this)) {
        securePlayback.setChecked(true);
    }
    securePlayback.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
          UserInfo.setSecurePlayback(SampleChooserActivity.this, isChecked);
          if (isChecked) {
            if (UserInfo.getSoftwareCodec(SampleChooserActivity.this)) {
                CheckBox softwareCodec = (CheckBox) findViewById(R.id.software_codec);
                softwareCodec.setChecked(false);
            }
          }
        }
    });

    CheckBox overlay = (CheckBox) findViewById(R.id.overlay);
    if (!UserInfo.getOverlay()) {
        overlay.setChecked(false);
    }
    overlay.setOnCheckedChangeListener(new OnCheckedChangeListener() {
          @Override
          public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
              UserInfo.setOverlay(isChecked);
              if (isChecked) {
                  if (UserInfo.getTunneledPlayback(SampleChooserActivity.this)) {
                      CheckBox tunneledPlayback = (CheckBox)findViewById(R.id.tunneled_playback);
                      tunneledPlayback.setChecked(false);
                  }
                  if (UserInfo.getSoftwareCodec(SampleChooserActivity.this)) {
                      CheckBox softwareCodec = (CheckBox) findViewById(R.id.software_codec);
                      softwareCodec.setChecked(false);
                  }
              }
          }
    });

    CheckBox softwareCodec = (CheckBox) findViewById(R.id.software_codec);
    if (UserInfo.getSoftwareCodec(this)) {
        softwareCodec.setChecked(true);
    }
    softwareCodec.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        UserInfo.setSoftwareCodec(SampleChooserActivity.this, isChecked);
        if (isChecked) {
            if (UserInfo.getTunneledPlayback(SampleChooserActivity.this)) {
                CheckBox tunneledPlayback = (CheckBox)findViewById(R.id.tunneled_playback);
                tunneledPlayback.setChecked(false);
            }
            if (UserInfo.getOverlay()) {
                CheckBox overlay = (CheckBox) findViewById(R.id.overlay);
                overlay.setChecked(false);
            }
            if (UserInfo.getSecurePlayback(SampleChooserActivity.this)) {
                CheckBox securePlayback = (CheckBox) findViewById(R.id.secure_playback);
                securePlayback.setChecked(false);
            }
        }
      }
    });

    CheckBox savees = (CheckBox) findViewById(R.id.savees);
    if (UserInfo.getSaveES()) {
        savees.setChecked(true);
    }
    savees.setOnCheckedChangeListener(new OnCheckedChangeListener() {
          @Override
          public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
              UserInfo.setSaveES(isChecked);
          }
    });

    CheckBox timeStats = (CheckBox)findViewById(R.id.time_stats);
    if (UserInfo.getTimeStats()) {
        timeStats.setChecked(true);
    }
    timeStats.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setTimeStats(isChecked);
        }
    });

    CheckBox mediaCodecLogcat = (CheckBox)findViewById(R.id.mediacodec_logcat);
    if (UserInfo.getMediaCodecLogcat()) {
        mediaCodecLogcat.setChecked(true);
    }
    mediaCodecLogcat.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setMediaCodecLogcat(isChecked);
        }
    });

    CheckBox aCodecLogcat = (CheckBox)findViewById(R.id.acodec_logcat);
    if (UserInfo.getACodecLogcat()) {
        aCodecLogcat.setChecked(true);
    }
    aCodecLogcat.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setACodecLogcat(isChecked);
        }
    });

    CheckBox audioTrackLogcat = (CheckBox)findViewById(R.id.audiotrack_logcat);
    if (UserInfo.getAudioTrackLogcat()) {
        audioTrackLogcat.setChecked(true);
    }
    audioTrackLogcat.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setAudioTrackLogcat(isChecked);
        }
    });

    CheckBox androidExtractor = (CheckBox)findViewById(R.id.android_extractor);
    if (UserInfo.getAndroidExtractor(this)) {
        androidExtractor.setChecked(true);
    }
    androidExtractor.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            UserInfo.setAndroidExtractor(SampleChooserActivity.this, isChecked);
        }
    });

    CheckBox browser = (CheckBox)findViewById(R.id.browser);
    browser.setOnCheckedChangeListener(new OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            if (isChecked) {
                ExpandableListView sampleList = (ExpandableListView) findViewById(R.id.sample_list);
                sampleList.setVisibility(View.GONE);

                ListView browserList = (ListView) findViewById(R.id.browser_list);
                browserList.setVisibility(View.VISIBLE);
                LocalFileAdapter listAdapter = new LocalFileAdapter(SampleChooserActivity.this);
                browserList.setAdapter(listAdapter);
                browserList.setOnItemClickListener(listAdapter);

                mBrowserFiles = true;
            } else {
                TextView currentPath = (TextView)findViewById(R.id.currentpath);
                currentPath.setVisibility(View.GONE);

                ListView browserList = (ListView) findViewById(R.id.browser_list);
                browserList.setVisibility(View.GONE);

                ExpandableListView sampleList = (ExpandableListView) findViewById(R.id.sample_list);
                sampleList.setVisibility(View.VISIBLE);

                showSampleList();

                mBrowserFiles = false;
            }
        }
    });

    showSampleList();
  }

  @Override
  public boolean onKeyDown(int keyCode, KeyEvent event) {
      if (mBrowserFiles) {
          ListView browserList = (ListView) findViewById(R.id.browser_list);
          LocalFileAdapter listAdapter = (LocalFileAdapter) browserList.getAdapter();
          boolean processed = listAdapter.onKeyDown(keyCode, event);
          if (processed) {
            return true;
          }
      }
      return super.onKeyDown(keyCode, event);
  }

  private void showSampleList() {
    final List<SampleGroup> sampleGroups = new ArrayList<SampleGroup>();
    SampleGroup group = new SampleGroup("YouTube DASH");
    group.addAll(Samples.YOUTUBE_DASH_MP4);
    group.addAll(Samples.YOUTUBE_DASH_WEBM);
    sampleGroups.add(group);
    group = new SampleGroup("Widevine DASH Policy Tests (GTS)");
    group.addAll(Samples.WIDEVINE_GTS);
    sampleGroups.add(group);
    group = new SampleGroup("Widevine HDCP Capabilities Tests");
    group.addAll(Samples.WIDEVINE_HDCP);
    sampleGroups.add(group);
    group = new SampleGroup("Widevine DASH: MP4,H264");
    group.addAll(Samples.WIDEVINE_H264_MP4_CLEAR);
    group.addAll(Samples.WIDEVINE_H264_MP4_SECURE);
    sampleGroups.add(group);
    group = new SampleGroup("Widevine DASH: WebM,VP9");
    group.addAll(Samples.WIDEVINE_VP9_WEBM_CLEAR);
    group.addAll(Samples.WIDEVINE_VP9_WEBM_SECURE);
    sampleGroups.add(group);
    group = new SampleGroup("Widevine DASH: MP4,H265");
    group.addAll(Samples.WIDEVINE_H265_MP4_CLEAR);
    group.addAll(Samples.WIDEVINE_H265_MP4_SECURE);
    sampleGroups.add(group);
    group = new SampleGroup("SmoothStreaming");
    group.addAll(Samples.SMOOTHSTREAMING);
    sampleGroups.add(group);
    group = new SampleGroup("HLS");
    group.addAll(Samples.HLS);
    sampleGroups.add(group);
    group = new SampleGroup("Misc");
    group.addAll(Samples.MISC);
    sampleGroups.add(group);
    ExpandableListView sampleList = (ExpandableListView) findViewById(R.id.sample_list);
    sampleList.setAdapter(new SampleAdapter(this, sampleGroups));
    sampleList.setOnChildClickListener(new OnChildClickListener() {
      @Override
      public boolean onChildClick(ExpandableListView parent, View view, int groupPosition,
          int childPosition, long id) {
        onSampleSelected(sampleGroups.get(groupPosition).samples.get(childPosition));
        return true;
      }
    });
  }

  private void onSampleSelected(Sample sample) {
    Intent mpdIntent = new Intent(this, PlayerActivity.class)
        .setData(Uri.parse(sample.uri))
        .putExtra(PlayerActivity.CONTENT_ID_EXTRA, sample.contentId)
        .putExtra(PlayerActivity.CONTENT_TYPE_EXTRA, sample.type)
        .putExtra(PlayerActivity.PROVIDER_EXTRA, sample.provider);
    startActivity(mpdIntent);
  }

  private static final class SampleAdapter extends BaseExpandableListAdapter {

    private final Context context;
    private final List<SampleGroup> sampleGroups;

    public SampleAdapter(Context context, List<SampleGroup> sampleGroups) {
      this.context = context;
      this.sampleGroups = sampleGroups;
    }

    @Override
    public Sample getChild(int groupPosition, int childPosition) {
      return getGroup(groupPosition).samples.get(childPosition);
    }

    @Override
    public long getChildId(int groupPosition, int childPosition) {
      return childPosition;
    }

    @Override
    public View getChildView(int groupPosition, int childPosition, boolean isLastChild,
        View convertView, ViewGroup parent) {
      View view = convertView;
      if (view == null) {
        view = LayoutInflater.from(context).inflate(android.R.layout.simple_list_item_1, parent,
            false);
      }
      ((TextView) view).setText(getChild(groupPosition, childPosition).name);
      return view;
    }

    @Override
    public int getChildrenCount(int groupPosition) {
      return getGroup(groupPosition).samples.size();
    }

    @Override
    public SampleGroup getGroup(int groupPosition) {
      return sampleGroups.get(groupPosition);
    }

    @Override
    public long getGroupId(int groupPosition) {
      return groupPosition;
    }

    @Override
    public View getGroupView(int groupPosition, boolean isExpanded, View convertView,
        ViewGroup parent) {
      View view = convertView;
      if (view == null) {
        view = LayoutInflater.from(context).inflate(R.layout.sample_chooser_inline_header, parent,
            false);
      }
      ((TextView) view).setText(getGroup(groupPosition).title);
      return view;
    }

    @Override
    public int getGroupCount() {
      return sampleGroups.size();
    }

    @Override
    public boolean hasStableIds() {
      return false;
    }

    @Override
    public boolean isChildSelectable(int groupPosition, int childPosition) {
      return true;
    }

  }

  private static final class SampleGroup {

    public final String title;
    public final List<Sample> samples;

    public SampleGroup(String title) {
      this.title = title;
      this.samples = new ArrayList<Sample>();
    }

    public void addAll(Sample[] samples) {
      Collections.addAll(this.samples, samples);
    }

  }

}
