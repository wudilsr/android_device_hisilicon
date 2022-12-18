package com.hisilicon.android.videoplayer.activity;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.ByteArrayInputStream;
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
import android.graphics.Bitmap;
import android.os.storage.IMountService;
import android.os.ServiceManager;
import android.os.IBinder;
import android.util.Log;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.activity.VideoActivity;
import com.hisilicon.android.videoplayer.activity.base.ActivityFrame;
import com.hisilicon.android.videoplayer.control.BDInfo;
import com.hisilicon.android.videoplayer.control.base.Constant;
import com.hisilicon.android.videoplayer.listmanager.FMMediaFileList;
import com.hisilicon.android.videoplayer.model.ModelBDInfo;
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
public class BDActivityNavigation extends ActivityFrame implements OnClickListener
{
    /** bluray poster */
    private ImageView mIvPoster;

    private Button mBtnPlayMovie;

    private Button mBtnSelectSection;

    /** bluray path */
    private String mPath;

    /** network file flag */
    private boolean mIsNetworkFile;

    private BDInfo mBDInfo;

    /** play progress memory */
    private String mMemory = "";

    /** init fail flag */
    private boolean mIsInitFail;

    private ReceiverNetwork mReceiverNetwork;

    private ReceiverUSB mReceiverUSB;

    private String mPosterCachePath;

    private boolean mUsePosterCache;

    private int mDefaultTitleId;

    private int mDefaultPlaylist;

    private GetInfoThread mGetInfoThread = null;

    private boolean mGetInfoThreadFlag = false;

    private GoPlayThread mGoPlayThread = null;

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
        mBDInfo.closeBluray();
        //finish();
        super.onPause();

        //finishActivityWithAnim();
    }

    @Override
    protected void onResume()
    {
        dismissProgressDialog();
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
                        if(mPath != null && mPath.startsWith("/mnt/iso") && mModelBDInfo != null)
                        {
                            LogTool.d("Umount BDISOPath:"+mModelBDInfo.getBDISOPath());
                            try
                            {
                                getMountService().unmountISO(tranString(mModelBDInfo.getBDISOPath()));
                            }
                            catch(Exception e)
                            {
                                LogTool.e("umount iso error:"+e);
                            }
                        }
                        mModelBDInfo = null;
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
        mBDInfo = new BDInfo();
        mModelBDInfo = new ModelBDInfo();
        mReceiverNetwork = new ReceiverNetwork(this);
        mReceiverUSB = new ReceiverUSB(this);

        mPosterCachePath = getApplicationInfo().dataDir + "/poster_cache";

        mDefaultTitleId = -1;
        mDefaultPlaylist = -1;
    }

    private void initListener()
    {
        mBtnPlayMovie.setOnClickListener(this);
        mBtnSelectSection.setOnClickListener(this);
    }

    private void bindData()
    {
        Intent _Intent = getIntent();

        ModelBDInfo _ModelBDInfo = (ModelBDInfo) _Intent.getSerializableExtra("bd");

        if (_ModelBDInfo == null)
        {
            mPath = _Intent.getStringExtra("path");
            mIsNetworkFile = _Intent.getBooleanExtra("isNetworkFile", false);

            getBDPathFromBDMVFile();

            if (mIsInitFail)
            {
                return;
            }

            getMovieNameFromBDPath();

            if (mPath.endsWith(".iso"))
                mBDInfo.openBluray("udf://"+mPath+"#");
            else
                mBDInfo.openBluray(mPath);

            if (mBDInfo.checkDiscInfo() < 0)
            {
                showQuitDialog(R.string.dialogTitleCheckDiscInfo,
                    R.string.dialogMessageCheckDiscInfo);
            }

            mModelBDInfo.setPath(mPath);
            mModelBDInfo.setNetworkFile(mIsNetworkFile);
            mModelBDInfo.setTitleNumber(mBDInfo.getTitleNumber());
        }
        else
        {
            if(_ModelBDInfo.getPath().endsWith(".iso"))
                mBDInfo.openBluray("udf://"+_ModelBDInfo.getPath()+"#");
            else
                mBDInfo.openBluray(_ModelBDInfo.getPath());
            mPath = _ModelBDInfo.getPath();
            mModelBDInfo = _ModelBDInfo;
            mModelBDInfo.setSelectSubtitleId(0);
            mModelBDInfo.setSelectAudioTrackId(0);
            mModelBDInfo.setTitleNumber(mBDInfo.getTitleNumber());
            getMovieNameFromBDPath();
            mModelBDInfo.setBDISOPath(_ModelBDInfo.getBDISOPath());
            mUsePosterCache = _ModelBDInfo.getPosterCache();
        }

        setPoster();
        enableButton();

        mGetInfoThread = new GetInfoThread();
        mGetInfoThread.start();
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
            _MD5 = MD5Tool.getFileMD5String(mModelBDInfo.getPath() + Constant.INDEX_BDMV);
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
        if(mDefaultTitleId != -1 && mDefaultPlaylist != -1)
        {
            mModelBDInfo.setSelectTitleId(mDefaultTitleId);
            //mModelBDInfo.setSelectTitleId(mBDInfo.getDefaultTitleId());
            mModelBDInfo.setSelectPlaylist(mDefaultPlaylist);
            //mModelBDInfo.setSelectPlaylist(mBDInfo.getDefaultPlaylist());
            mModelBDInfo.setChapterPosition(0);
            mModelBDInfo.setChapterNumber(mBDInfo.getChapterNumberByTitleId(mModelBDInfo
                .getSelectTitleId()));

            play();
        }
        else
        {
            showLoadProgressDialog();
            mGoPlayThread = new GoPlayThread();
            mGoPlayThread.start();
        }
    }

    private void continuePlay()
    {
        LogTool.d("");
        String[] _Memorys = mMemory.split(" ");
        int _TitleId = Integer.parseInt(_Memorys[0]);
        int _CurPosition = Integer.parseInt(_Memorys[1]);

        mModelBDInfo.setSelectTitleId(_TitleId);
        mModelBDInfo.setChapterNumber(mBDInfo.getChapterNumberByTitleId(_TitleId));
        mModelBDInfo.setSelectPlaylist(mBDInfo.getPlaylistByTitleId(_TitleId));
        mModelBDInfo.setChapterPosition(_CurPosition);

        play();
    }

    private void play()
    {
        LogTool.d("");
        Intent _Intent = new Intent(BDActivityNavigation.this, VideoActivity.class);
        StringBuffer _Buf = new StringBuffer();
        if(mModelBDInfo.getPath().endsWith(".iso"))
        {
            _Buf.append(Constant.BD_PREFIX);
            _Buf.append("udf://");
            _Buf.append(mModelBDInfo.getPath());
            _Buf.append("#?playlist=");
            _Buf.append(mModelBDInfo.getSelectPlaylist());
        }
        else
        {
            _Buf.append(Constant.BD_PREFIX);
            _Buf.append(mModelBDInfo.getPath());
            _Buf.append("?playlist=");
            _Buf.append(mModelBDInfo.getSelectPlaylist());
        }
        FMMediaFileList _FMMediaFileList = new FMMediaFileList(_Buf.toString(),mModelBDInfo.getMovieName());
        _Intent.putExtra("MediaFileList", _FMMediaFileList);
        mUsePosterCache = true;
        mModelBDInfo.setPosterCache(mUsePosterCache);
        startActivityWithAnim(_Intent);
    }

    private void selectSection()
    {
        LogTool.d("");
        new AsyncTaskTitle().execute("");
    }

    private void getMovieNameFromBDPath()
    {
        LogTool.d("");
        if (mPath == null)
        {
            return;
        }

        if (mPath.endsWith(".iso"))
        {
            String _Name = getIntent().getStringExtra("BDISOName");
            String _Path = getIntent().getStringExtra("BDISOPath");
            mModelBDInfo.setMovieName(_Name);
            mModelBDInfo.setBDISOPath(_Path);
            return;
        }

        int _Index = mPath.lastIndexOf(File.separatorChar);

        if ((_Index >= 0) && (_Index < mPath.length()))
        {
            mModelBDInfo.setMovieName(mPath.substring(_Index + 1, mPath.length()));
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

        byte[] data = mBDInfo.getPoster();
        if(data != null)
        {
            Bitmap bitMap = BitmapFactory.decodeByteArray(data, 0, data.length);
            if(bitMap != null)
            {
                mIvPoster.setImageBitmap(bitMap);
                final InputStream mInputStream = new ByteArrayInputStream(data);
                new Thread()
                {
                    @Override
                    public void run()
                    {
                        try
                        {
                            FileTool.cp(mInputStream, mPosterCachePath);
                        }
                        catch (IOException pIOException)
                        {
                            pIOException.printStackTrace();
                        }
                        finally
                        {
                            try
                            {
                                if(mInputStream != null)
                                    mInputStream.close();
                            }
                            catch (IOException pIOException)
                            {
                                pIOException.printStackTrace();
                            }
                        }
                    }
                }.start();
            }
        }
        else
        {
            mIvPoster.setImageResource(R.drawable.poster_default_bd);
        }
    }

    private void showTitleListDialog(String[] pTitleInfo)
    {
        LogTool.d("");
        AlertDialog.Builder _Builder = new AlertDialog.Builder(this);
        _Builder.setTitle(getString(R.string.dialogTitleTitleSelect, new Object[]
        { mModelBDInfo.getTitleNumber() }));
        _Builder.setSingleChoiceItems(pTitleInfo, mModelBDInfo.getSelectTitleId(),
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
        { mModelBDInfo.getChapterNumber() }));
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
            mModelBDInfo.setSelectTitleId(pWhich);
            mModelBDInfo.setSelectPlaylist(mBDInfo.getPlaylistByTitleId(mModelBDInfo
                .getSelectTitleId()));
            pDialog.dismiss();
            new AsyncTaskChapter().execute("");
        }
    }

    private class OnChapterListDialogClickListener implements DialogInterface.OnClickListener
    {
        public void onClick(DialogInterface pDialog, int pWhich)
        {
            mModelBDInfo.setSelectChapterId(pWhich);
            mModelBDInfo.setChapterPosition(mBDInfo.getChapterPosition(
                mModelBDInfo.getSelectTitleId(), mModelBDInfo.getSelectChapterId()));
            pDialog.dismiss();

            mModelBDInfo.setSelectSubtitleId(0);
            mModelBDInfo.setSelectAudioTrackId(0);

            play();
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

            int _TitleNumber = mModelBDInfo.getTitleNumber();
            for (int i = 0; i < _TitleNumber; i++)
            {
                publishProgress(100 * (i + 1) / _TitleNumber);
                _List.add(getString(R.string.listItemTitle, new Object[]
                { i + 1, TimeTool.mill2String(mBDInfo.getDurationByTitleId(i)) }));
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
            int _TitleId = mModelBDInfo.getSelectTitleId();
            mModelBDInfo.setChapterNumber(mBDInfo.getChapterNumberByTitleId(_TitleId));

            int _ChapterNumber = mModelBDInfo.getChapterNumber();
            for (int i = 0; i < _ChapterNumber; i++)
            {
                _List.add(getString(R.string.listItemChapter, new Object[]
                { i + 1, TimeTool.mill2String(mBDInfo.getChapterPosition(_TitleId, i)) }));
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
    private class GetInfoThread extends Thread
    {
        public void run()
        {
            LogTool.d("Begin to get default playlist!");
            mGetInfoThreadFlag = true;
            mDefaultTitleId = mBDInfo.getDefaultTitleId();
            mDefaultPlaylist = mBDInfo.getDefaultPlaylist();
            mGetInfoThreadFlag = false;
        }
    }
    private class GoPlayThread extends Thread
    {
        public void run()
        {
            LogTool.d("Begin to play movie!");
            while(mGetInfoThreadFlag)
            {
                try
                {
                    Thread.sleep(10);
				}
                catch (InterruptedException e)
                {
                    e.printStackTrace();
				}
            }
            if(mDefaultTitleId != -1)
                mModelBDInfo.setSelectTitleId(mDefaultTitleId);
            else
                mModelBDInfo.setSelectTitleId(mBDInfo.getDefaultTitleId());
            if(mDefaultPlaylist != -1)
                mModelBDInfo.setSelectPlaylist(mDefaultPlaylist);
            else
                mModelBDInfo.setSelectPlaylist(mBDInfo.getDefaultPlaylist());
            mModelBDInfo.setChapterPosition(0);
            mModelBDInfo.setChapterNumber(mBDInfo.getChapterNumberByTitleId(mModelBDInfo
                .getSelectTitleId()));

            play();
        }
    }
}
