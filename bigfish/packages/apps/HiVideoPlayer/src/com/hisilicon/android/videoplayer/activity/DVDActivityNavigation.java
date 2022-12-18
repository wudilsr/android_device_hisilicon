package com.hisilicon.android.videoplayer.activity;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.os.storage.IMountService;
import android.os.ServiceManager;
import android.os.IBinder;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.activity.VideoActivity;
import com.hisilicon.android.videoplayer.activity.base.ActivityFrame;
import com.hisilicon.android.videoplayer.control.DVDInfo;
import com.hisilicon.android.videoplayer.control.base.Constant;
import com.hisilicon.android.videoplayer.listmanager.FMMediaFileList;
import com.hisilicon.android.videoplayer.model.ModelDVDInfo;
import com.hisilicon.android.videoplayer.receiver.ReceiverNetwork;
import com.hisilicon.android.videoplayer.receiver.ReceiverUSB;
import com.hisilicon.android.videoplayer.utility.DialogTool;
import com.hisilicon.android.videoplayer.utility.FileTool;
import com.hisilicon.android.videoplayer.utility.LogTool;
import com.hisilicon.android.videoplayer.utility.MD5Tool;
import com.hisilicon.android.videoplayer.utility.TimeTool;
import com.hisilicon.android.videoplayer.utility.ViewTool;
import com.hisilicon.android.videoplayer.utility.base.ImageFileFilter;


/**
 * ActivityNavigation: HiBPlayer navigation interface
 */
public class DVDActivityNavigation extends ActivityFrame implements OnClickListener
{
    /** bluray poster */
    private ImageView mIvPoster;

    private Button mBtnPlayMovie;

    private Button mBtnSelectSection;

    /** bluray path */
    private String mPath;

    /** network file flag */
    private boolean mIsNetworkFile;

    private DVDInfo mDVDInfo;

    /** play progress memory */
    private String mMemory = "";

    /** init fail flag */
    private boolean mIsInitFail;

    private ReceiverNetwork mReceiverNetwork;

    private ReceiverUSB mReceiverUSB;

    private String mPosterCachePath;

    private boolean mUsePosterCache;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        LogTool.v("");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_navigation);

        hideStatusbar();
        pauseBackgroundMusic(getApplicationContext());
        initView();
        initVariable();
        initListener();
    }

    @Override
    protected void onStop()
    {
        LogTool.v("");
        super.onStop();
    }

    @Override
    protected void onPause()
    {
        LogTool.v("");
        mDVDInfo.closeDVD();
        finish();
        super.onPause();
    }

    @Override
    protected void onResume()
    {
        LogTool.v("");
        bindData();
        super.onResume();
    }

    @Override
    protected void onDestroy()
    {
        LogTool.v("");
        super.onDestroy();
    }

    private void deletePosterCache()
    {
        LogTool.d("");
        File _File = new File(mPosterCachePath);
        if (_File.exists())
        {
            _File.delete();
        }
    }
    @Override
    public boolean onKeyDown(int pKeyCode, KeyEvent pEvent)
    {
        boolean _IsValid = false;

        switch (pKeyCode)
        {
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_ESCAPE:
                    {
                        deletePosterCache();
                        if(mPath != null && mPath.startsWith("/mnt/iso") && mModelDVDInfo != null)
                        {
                            LogTool.d("Umount DVDISOPath:"+mModelDVDInfo.getDVDISOPath());
                            try
                            {
                                getMountService().unmountISO(tranString(mModelDVDInfo.getDVDISOPath()));
                            }
                            catch(Exception e)
                            {
                                LogTool.e("umount iso error:"+e);
                            }
                        }
                        mModelDVDInfo = null;
                        _IsValid = true;
                        finish();
                        break;
                    }
            default:
                    break;
        }
        if (_IsValid)
        {
            return true;
        }
        return super.onKeyDown(pKeyCode, pEvent);
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent pEvent)
    {
        int _KeyCode = pEvent.getKeyCode();

        boolean _IsValid = false;

        switch (_KeyCode)
        {
            case KeyEvent.KEYCODE_DPAD_CENTER:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_VOLUME_DOWN:
            case KeyEvent.KEYCODE_VOLUME_UP:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_ESCAPE:
            case KeyEvent.KEYCODE_MENU:
            case Constant.KeyCode.KEYCODE_MEDIA_MUTE:
                _IsValid = true;
                break;

            default:
                break;
        }

        if (!_IsValid)
        {
            return true;
        }

        return super.dispatchKeyEvent(pEvent);
    }

    private void initView()
    {
        mIvPoster = (ImageView) findViewById(R.id.ivPoster);
        mBtnPlayMovie = (Button) findViewById(R.id.btnPlayMovie);
        mBtnSelectSection = (Button) findViewById(R.id.btnSelectSection);
    }

    private void initVariable()
    {
        mDVDInfo = new DVDInfo();
        mModelDVDInfo = new ModelDVDInfo();
        mReceiverNetwork = new ReceiverNetwork(this);
        mReceiverUSB = new ReceiverUSB(this);

        mPosterCachePath = getApplicationInfo().dataDir + "/poster_cache";
    }

    private void initListener()
    {
        mBtnPlayMovie.setOnClickListener(this);
        mBtnSelectSection.setOnClickListener(this);
    }

    private void bindData()
    {
        Intent _Intent = getIntent();

        ModelDVDInfo _ModelDVDInfo = (ModelDVDInfo) _Intent.getSerializableExtra("dvd");

        if (_ModelDVDInfo == null)
        {
            mPath = _Intent.getStringExtra("path");
            mIsNetworkFile = _Intent.getBooleanExtra("isNetworkFile", false);

            //getBDPathFromBDMVFile();

            if (mIsInitFail)
            {
                return;
            }

            getMovieNameFromDVDPath();

            mDVDInfo.openDVD(mPath);

            if (mDVDInfo.checkDiscInfo() < 0)
            {
                showQuitDialog(R.string.dialogTitleCheckDiscInfo,
                    R.string.dialogMessageCheckDiscInfo);
            }

            mModelDVDInfo.setPath(mPath);
            mModelDVDInfo.setNetworkFile(mIsNetworkFile);
            mModelDVDInfo.setTitleNumber(mDVDInfo.getTitleNumber());
        }
        else
        {
            mDVDInfo.openDVD(_ModelDVDInfo.getPath());
            mPath = _ModelDVDInfo.getPath();
            mModelDVDInfo = _ModelDVDInfo;
            mModelDVDInfo.setSelectSubtitleId(0);
            mModelDVDInfo.setSelectAudioTrackId(0);
            mModelDVDInfo.setTitleNumber(mDVDInfo.getTitleNumber());
            getMovieNameFromDVDPath();
            mModelDVDInfo.setDVDISOPath(_ModelDVDInfo.getDVDISOPath());
            mUsePosterCache = _ModelDVDInfo.getPosterCache();
        }

        setPoster();
        enableButton();
    }

    /**
     * load play progress memory
     */
    private void loadMemory()
    {
        LogTool.d("");
        String _MD5 = null;

        try
        {
            _MD5 = MD5Tool.getFileMD5String(mModelDVDInfo.getPath() + Constant.INDEX_BDMV);
        }
        catch (Exception pException)
        {
            pException.printStackTrace();
            return;
        }

        SharedPreferences _SPF = getSharedPreferences(Constant.SPF_FILENAME, Activity.MODE_PRIVATE);
        mMemory = _SPF.getString(_MD5, "");
        if (!mMemory.equals(""))
        {
            // memory exists
            showContinueDialog();
            SharedPreferences.Editor _Editor = getSharedPreferences(Constant.SPF_FILENAME, Activity.MODE_PRIVATE).edit();
            _Editor.remove(_MD5);
            _Editor.commit();
        }
        else
        {
            // first play
            play();
        }
    }

    private void enableButton()
    {
        ViewTool.enableClick(mBtnPlayMovie);
        ViewTool.enableClick(mBtnSelectSection);
    }

    public void onClick(View pView)
    {
        switch (pView.getId())
        {
            case R.id.btnPlayMovie:
                playMovie();
                break;

            case R.id.btnSelectSection:
                selectSection();
                break;

            default:
                break;
        }
    }

    private void playMovie()
    {
        LogTool.d("");

        mModelDVDInfo.setChapterPosition(0);
        mModelDVDInfo.setChapterNumber(mDVDInfo.getChapterNumberByTitleId(mModelDVDInfo
            .getSelectTitleId()));

        play();
    }

    private void continuePlay()
    {
        LogTool.d("");
        String[] _Memorys = mMemory.split(" ");
        int _TitleId = Integer.parseInt(_Memorys[0]);
        int _CurPosition = Integer.parseInt(_Memorys[1]);

        mModelDVDInfo.setSelectTitleId(_TitleId);
        mModelDVDInfo.setChapterNumber(mDVDInfo.getChapterNumberByTitleId(_TitleId));
        mModelDVDInfo.setSelectPlaylist(mDVDInfo.getPlaylistByTitleId(_TitleId));
        mModelDVDInfo.setChapterPosition(_CurPosition);

        play();
    }

    private void play()
    {
        LogTool.d("");
        Intent _Intent = new Intent(DVDActivityNavigation.this, VideoActivity.class);
        StringBuffer _Buf = new StringBuffer();
        _Buf.append(Constant.DVD_PREFIX);
        _Buf.append(mModelDVDInfo.getPath());
        FMMediaFileList _FMMediaFileList = new FMMediaFileList(_Buf.toString(),mModelDVDInfo.getMovieName());
        _Intent.putExtra("MediaFileList", _FMMediaFileList);
        mUsePosterCache = true;
        mModelDVDInfo.setPosterCache(mUsePosterCache);
        startActivityWithAnim(_Intent);
    }

    private void playChapter()
    {
        LogTool.d("");
        Intent _Intent = new Intent(DVDActivityNavigation.this, VideoActivity.class);
        StringBuffer _Buf = new StringBuffer();
        _Buf.append(Constant.DVD_PREFIX);
        _Buf.append(mModelDVDInfo.getPath());
        _Buf.append("?title=");
        _Buf.append(mModelDVDInfo.getSelectTitleId());
        FMMediaFileList _FMMediaFileList = new FMMediaFileList(_Buf.toString(),mModelDVDInfo.getMovieName());
        _Intent.putExtra("MediaFileList", _FMMediaFileList);
        mUsePosterCache = true;
        mModelDVDInfo.setPosterCache(mUsePosterCache);
        startActivityWithAnim(_Intent);
    }

    private void selectSection()
    {
        LogTool.d("");
        new AsyncTaskTitle().execute("");
    }

    private void getMovieNameFromDVDPath()
    {
        LogTool.d("");
        if (mPath == null)
        {
            return;
        }

        if (mPath.startsWith("/mnt/iso"))
        {
            String _Name = getIntent().getStringExtra("DVDISOName");
            String _Path = getIntent().getStringExtra("DVDISOPath");
            mModelDVDInfo.setMovieName(_Name);
            mModelDVDInfo.setDVDISOPath(_Path);
            return;
        }

        int _Index = mPath.lastIndexOf(File.separatorChar);

        if ((_Index >= 0) && (_Index < mPath.length()))
        {
            mModelDVDInfo.setMovieName(mPath.substring(_Index + 1, mPath.length()));
        }
    }

    /**
     * get bluray path from .bdmv file
     */
    private void getBDPathFromBDMVFile()
    {
        LogTool.d("");

        if (mPath == null)
        {
            showQuitDialog(R.string.dialogTitleCheckIntent, R.string.dialogMessageCheckIntent);
            return;
        }

        if (!mPath.endsWith(".bdmv"))
        {
            // bluray path instead of .bdmv file
            return;
        }

        File _File = null;
        boolean _isLooping = true;

        // find dir whose subdir is BDMV
        while (_isLooping)
        {
            mPath = truncStringByLastChar(mPath, File.separatorChar);

            if (mPath.equals(""))
            {
                _isLooping = false;
                showQuitDialog(R.string.dialogTitleCheckPath, R.string.dialogMessageCheckPath);
                return;
            }

            _File = new File(mPath);

            File[] _SubFiles = _File.listFiles();

            if (_SubFiles == null)
            {
                break;
            }

            for (int i = 0; i < _SubFiles.length; i++)
            {
                if (_SubFiles[i].isDirectory() && _SubFiles[i].getName().equals("BDMV"))
                {
                    _isLooping = false;
                }
            }
        }
    }

    private String truncStringByLastChar(String pString, int pChar)
    {
        int _Index = pString.lastIndexOf(pChar);

        if ((_Index >= 0) && (_Index < pString.length()))
        {
            pString = pString.substring(0, _Index);
        }

        return pString;
    }

    private void setPoster()
    {
        LogTool.d("");

        if(!mUsePosterCache)
            deletePosterCache();

        File _PosterCache = new File(mPosterCachePath);

        if (_PosterCache.exists() && mUsePosterCache)
        {
            mIvPoster.setImageBitmap(BitmapFactory.decodeFile(mPosterCachePath));
            return;
        }

        mIvPoster.setImageResource(R.drawable.poster_default_dvd);
    }

    private void showTitleListDialog(String[] pTitleInfo)
    {
        LogTool.d("");
        AlertDialog.Builder _Builder = new AlertDialog.Builder(this);
        _Builder.setTitle(getString(R.string.dialogTitleTitleSelect, new Object[]
        { mModelDVDInfo.getTitleNumber() }));
        _Builder.setSingleChoiceItems(pTitleInfo, (mModelDVDInfo.getSelectTitleId()-1)<0?0:(mModelDVDInfo.getSelectTitleId()-1),
            new OnTitleListDialogClickListener());
        Dialog _Dialog = _Builder.show();
        DialogTool.disableBackgroundDim(_Dialog);
        DialogTool.setDefaultSelectDisplay(_Dialog);
    }

    private void showChapterListDialog(String[] pChapterInfo)
    {
        LogTool.d("");
        AlertDialog.Builder _Builder = new AlertDialog.Builder(this);
        _Builder.setTitle(getString(R.string.dialogTitleChapterSelect, new Object[]
        { mModelDVDInfo.getChapterNumber() }));
        _Builder.setSingleChoiceItems(pChapterInfo, 0, new OnChapterListDialogClickListener());
        Dialog _Dialog = _Builder.show();
        DialogTool.disableBackgroundDim(_Dialog);
        DialogTool.setDefaultSelectDisplay(_Dialog);
    }

    private void showContinueDialog()
    {
        LogTool.d("");
        Dialog _Dialog =
            getDoubleOperationDialog(R.string.dialogTitleContinue, R.string.dialogMessageContinue,
                new OnContinueDialogClickListener());
        _Dialog.setOnCancelListener(new OnContinueDialogCancelListener());
        DialogTool.disableBackgroundDim(_Dialog);
        DialogTool.setDefaultTipDisplay(_Dialog);
    }

    private void showQuitDialog(int pTitleId, int pMessageId)
    {
        LogTool.d("");
        Dialog _Dialog =
            getSingleOperationDialog(pTitleId, pMessageId, new OnQuitDialogClickListener());
        DialogTool.disableBackgroundDim(_Dialog);
        DialogTool.setDefaultTipDisplay(_Dialog);
        mIsInitFail = true;
    }

    private class OnTitleListDialogClickListener implements DialogInterface.OnClickListener
    {
        public void onClick(DialogInterface pDialog, int pWhich)
        {
            mModelDVDInfo.setSelectTitleId(pWhich+1);
            mModelDVDInfo.setSelectPlaylist(mDVDInfo.getPlaylistByTitleId(mModelDVDInfo
                .getSelectTitleId()));
            pDialog.dismiss();
            new AsyncTaskChapter().execute("");
        }
    }

    private class OnChapterListDialogClickListener implements DialogInterface.OnClickListener
    {
        public void onClick(DialogInterface pDialog, int pWhich)
        {
            mModelDVDInfo.setSelectChapterId(pWhich);
            mModelDVDInfo.setChapterPosition(mDVDInfo.getChapterPosition(
                mModelDVDInfo.getSelectTitleId(), mModelDVDInfo.getSelectChapterId()));
            pDialog.dismiss();

            mModelDVDInfo.setSelectSubtitleId(0);
            mModelDVDInfo.setSelectAudioTrackId(0);

            playChapter();
        }
    }

    private class OnContinueDialogClickListener implements DialogInterface.OnClickListener
    {
        public void onClick(DialogInterface pDialog, int pWhich)
        {
            switch (pWhich)
            {
                case Constant.Button.YES:
                    pDialog.dismiss();
                    continuePlay();
                    break;

                case Constant.Button.NO:
                    pDialog.dismiss();
                    play();
                    break;

                default:
                    break;
            }
        }
    }

    private class OnContinueDialogCancelListener implements DialogInterface.OnCancelListener
    {
        public void onCancel(DialogInterface pDialog)
        {
            pDialog.dismiss();
            play();
        }
    }

    private class OnQuitDialogClickListener implements DialogInterface.OnClickListener
    {
        public void onClick(DialogInterface pDialog, int pWhich)
        {
            finishActivityWithAnim();
        }
    }

    private class AsyncTaskTitle extends AsyncTask<String, Integer, String[]>
    {
        @Override
        protected void onPreExecute()
        {
            showLoadProgressDialog();
            super.onPreExecute();
        }

        @Override
        protected String[] doInBackground(String... pParams)
        {
            List<String> _List = new ArrayList<String>();
            String[] _Strings = new String[_List.size()];

            int _TitleNumber = mModelDVDInfo.getTitleNumber();
            for (int i = 0; i < _TitleNumber; i++)
            {
                publishProgress(100 * (i + 1) / _TitleNumber);
                _List.add(getString(R.string.listItemTitle, new Object[]
                { i + 1, TimeTool.mill2String(mDVDInfo.getDurationByTitleId(i+1)) }));
            }

            return _List.toArray(_Strings);
        }

        @Override
        protected void onPostExecute(String[] pResult)
        {
            dismissProgressDialog();
            showTitleListDialog(pResult);
            super.onPostExecute(pResult);
        }
    }

    private class AsyncTaskChapter extends AsyncTask<String, Integer, String[]>
    {
        @Override
        protected void onPreExecute()
        {
            showLoadProgressDialog();
            super.onPreExecute();
        }

        @Override
        protected String[] doInBackground(String... pParams)
        {
            List<String> _List = new ArrayList<String>();
            String[] _Strings = new String[_List.size()];
            int _TitleId = mModelDVDInfo.getSelectTitleId();
            mModelDVDInfo.setChapterNumber(mDVDInfo.getChapterNumberByTitleId(_TitleId));

            int _ChapterNumber = mModelDVDInfo.getChapterNumber();
            for (int i = 0; i < _ChapterNumber; i++)
            {
                _List.add(getString(R.string.listItemChapter, new Object[]
                { i + 1, TimeTool.mill2String(mDVDInfo.getChapterPosition(_TitleId, i)) }));
            }

            return _List.toArray(_Strings);
        }

        @Override
        protected void onPostExecute(String[] pResult)
        {
            dismissProgressDialog();
            showChapterListDialog(pResult);
            super.onPostExecute(pResult);
        }
    }
    protected String tranString(String path)
    {
        String tranPath = "";
        for (int i = 0; i < path.length(); i++) {
            tranPath += "\\" + path.substring(i, i + 1);
        }

        return tranPath;
    }
    private static IMountService getMountService() {
		IBinder service = ServiceManager.getService("mount");
		if (service != null) {
			return IMountService.Stub.asInterface(service);
		} else {
			LogTool.e("Can't get mount service");
		}
		return null;
	}
}
