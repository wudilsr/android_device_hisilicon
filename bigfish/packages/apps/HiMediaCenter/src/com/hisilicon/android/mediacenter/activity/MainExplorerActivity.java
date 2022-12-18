package com.hisilicon.android.mediacenter.activity;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.DialogInterface.OnCancelListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SubMenu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.CheckedTextView;
import android.widget.ExpandableListView;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ExpandableListView.OnChildClickListener;

import com.hisilicon.android.mediacenter.common.CommonActivity;
import com.hisilicon.android.mediacenter.common.ControlListAdapter;
import com.hisilicon.android.mediacenter.common.ExpandAdapter;
import com.hisilicon.android.mediacenter.common.FileAdapter;
import com.hisilicon.android.mediacenter.common.FileUtil;
import com.hisilicon.android.mediacenter.common.FilterType;
import com.hisilicon.android.mediacenter.common.GroupInfo;
import com.hisilicon.android.mediacenter.common.MountInfo;
import com.hisilicon.android.mediacenter.common.NewCreateDialog;
import com.hisilicon.android.mediacenter.R;

import android.net.Uri;

import android.os.storage.IMountService;
import android.os.ServiceManager;
import android.os.IBinder;

import com.hisilicon.android.sdkinvoke.HiSdkinvoke;

/**
 * The local file browsing
 * CNcomment:本地文件浏览
 */
public class MainExplorerActivity extends CommonActivity {

	private static final String TAG = "MainExplorerActivity";

	private String parentPath = "";

	// Operation File list
	// CNcomment:操作文件列表
	private List<File> fileArray = null;

	private String directorys = "/sdcard";

	// The list of files click position
	// CNcomment:文件列表的点击位置
	private int myPosition = 0;

	int Num = 0;

	int tempLength = 0;

	// file list selected
	// CNcomment:选中的文件列表
	List<String> selectList = null;

	// operation list
	// CNcomment:操作列表
	ListView list;

	// mount list
	// CNcomment:挂载列表
	List<Map<String, Object>> sdlist;

	int clickCount = 0;

	AlertDialog dialog;

	// store the Click position set
	// CNcomment:存放点击位置集合
	List<Integer> intList;

	// Need to sort the file list
	// CNcomment:需要排序的文件列表
	File[] sortFile;

	final static String MOUNT_LABLE = "mountLable";

	final static String MOUNT_TYPE = "mountType";

	final static String MOUNT_PATH = "mountPath";

	final static String MOUNT_NAME = "mountName";

	final static String MUSIC_PATH = "music_path";

	int menu_item = 0;

	ExpandableListView expandableListView;

	// Device type node-set
	// CNcomment:设备类型节点集合
	List<GroupInfo> groupList;

	// sub notes set of equipment
	// CNcomment:设备子节点集合
	List<Map<String, String>> childList;

	// Device List Category Location
	// CNcomment:设备列表类别位置
	int groupPosition = -1;

	// Index Display
	// CNcomment:索引显示
	TextView numInfo;;

	// Intent transfer from VP
	// CNcomment:Intent从VP传输
	boolean subFlag = false;

    boolean hasCDROM = false;

	FileUtil util;

	private String isoParentPath = new String();

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);
        String chipVersion = HiSdkinvoke.getChipVersion();
        Log.i(TAG,"chipVersion:"+chipVersion);
        if(chipVersion.equals("Unknown chip ID"))
            finish();
		FilterType.filterType(MainExplorerActivity.this);
		init();
		selectList = new ArrayList<String>();
		getUSB();
	}

	private void init() {

		// sortBut = (ImageButton) findViewById(R.id.sortBut);

		//filterBut = (ImageButton) findViewById(R.id.filterBut);

		intList = new ArrayList<Integer>();
		listFile = new ArrayList<File>();
		gridlayout = R.layout.gridfile_row;
		listlayout = R.layout.file_row;
		listView = (ListView) findViewById(R.id.listView);
		gridView = (GridView) findViewById(R.id.gridView);

		pathTxt = (TextView) findViewById(R.id.pathTxt);

		numInfo = (TextView) findViewById(R.id.ptxt);

		expandableListView = (ExpandableListView) findViewById(R.id.expandlistView);
		getsdList();

		isNetworkFile = false;
	}

	/**
	 * Obtain mount list
	 * CNcomment:获得挂载列表
	 */
	public void getsdList() {

		getMountEquipmentList();
		ExpandAdapter adapter = new ExpandAdapter(this, groupList);
		expandableListView.setAdapter(adapter);
		for (int i = 0; i < groupList.size(); i++) {
			expandableListView.expandGroup(i);
		}

		expandableListView.setOnChildClickListener(new OnChildClickListener() {
			public boolean onChildClick(ExpandableListView parent, View v,
					int groupPosition, int childPosition, long id) {
				String path = groupList.get(groupPosition).getChildList()
						.get(childPosition).get(MOUNT_PATH);
				File dvdFile = new File(path);
                if (dvdFile.exists() && dvdFile.isDirectory() && mIsSupportBD &&
                    FileUtil.getMIMEType(dvdFile, MainExplorerActivity.this).equals("video/dvd")) {
                    preCurrentPath = "";
                    Intent intent = new Intent();
                    intent.setClassName(
                            "com.hisilicon.android.videoplayer",
                            "com.hisilicon.android.videoplayer.activity.MediaFileListService");
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    intent.setDataAndType(Uri.parse(path), "video/bd");
                    intent.putExtra("sortCount", sortCount);
                    intent.putExtra("isNetworkFile", isNetworkFile);
                    startService(intent);
                } else {
                    mountSdPath = path;
                    MainExplorerActivity.this.groupPosition = groupPosition;
                    arrayFile.clear();
                    arrayDir.clear();
                    directorys = path;
                    expandableListView.setVisibility(View.INVISIBLE);
                    listView.setVisibility(View.VISIBLE);
                    listFile.clear();
                    clickPos = 0;
                    myPosition = 0;
                    // FileAdapter adapter = new FileAdapter(
                    // MainExplorerActivity.this, li, listlayout);
                    // listView.setAdapter(adapter);
                    geDdirectory(directorys);
                    intList.add(childPosition);
                    updateList(true);
                }
				return false;
			}
		});
	}

	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		SubMenu operatFile = menu.addSubMenu(Menu.NONE, Menu.NONE, 0,
				getString(R.string.operation));
		operatFile.add(Menu.NONE, MENU_COPY, 0, getString(R.string.copy));
		operatFile.add(Menu.NONE, MENU_CUT, 0, getString(R.string.cut));
		operatFile.add(Menu.NONE, MENU_PASTE, 0, getString(R.string.paste));
		operatFile.add(Menu.NONE, MENU_DELETE, 0, getString(R.string.delete));
		operatFile.add(Menu.NONE, MENU_RENAME, 0,
				getString(R.string.str_rename));
		operatFile.add(Menu.NONE, MENU_DEFAULT_PATH, 0, R.string.default_path);

		menu.add(Menu.NONE, MENU_ADD, 0, getString(R.string.str_new));
		menu.add(Menu.NONE, MENU_SEARCH, 0, getString(R.string.search));
        menu.add(Menu.NONE, MENU_CD_ROM, 0, getString(R.string.eject_cdrom));
		return true;
	};

	public boolean onPrepareOptionsMenu(Menu menu) {

		SharedPreferences share = getSharedPreferences("OPERATE", SHARE_MODE);
		int num = share.getInt("NUM", 0);
        if (!OPERATER_ENABLE) {
            menu.getItem(0).setVisible(false);
        }
		if (!pathTxt.getText().toString().equals("")) {
			// menu.getItem(4).setEnabled(true);
			// menu.getItem(5).setEnabled(true);
			if (listFile.size() == 0) {
				menu.getItem(0).getSubMenu().getItem(0).setEnabled(false);
				menu.getItem(0).getSubMenu().getItem(1).setEnabled(false);
				menu.getItem(0).getSubMenu().getItem(3).setEnabled(false);
				menu.getItem(0).getSubMenu().getItem(4).setEnabled(false);
				menu.getItem(0).getSubMenu().getItem(5).setEnabled(false);
				// menu.getItem(3).getSubMenu().getItem(5).setEnabled(false);
				if (num == 0) {
					menu.getItem(0).setEnabled(false);
				} else {
					menu.getItem(0).setEnabled(true);
					menu.getItem(0).getSubMenu().getItem(2).setEnabled(true);
				}
				menu.getItem(1).setEnabled(true);
				menu.getItem(2).setEnabled(false);
                menu.getItem(3).setEnabled(false);
			} else {
				menu.getItem(0).setEnabled(true);
				menu.getItem(0).getSubMenu().getItem(0).setEnabled(true);
				menu.getItem(0).getSubMenu().getItem(1).setEnabled(true);
				menu.getItem(0).getSubMenu().getItem(3).setEnabled(true);
				menu.getItem(0).getSubMenu().getItem(4).setEnabled(true);
				menu.getItem(0).getSubMenu().getItem(5).setEnabled(true);
				// if (arrayFile.size() == 0) {
				// menu.getItem(3).getSubMenu().getItem(5).setEnabled(false);
				// } else {
				// menu.getItem(3).getSubMenu().getItem(5).setEnabled(true);
				// }
				if (num == 0) {
					menu.getItem(0).getSubMenu().getItem(2).setEnabled(false);
				} else {
					menu.getItem(0).getSubMenu().getItem(2).setEnabled(true);
				}
				menu.getItem(0).setEnabled(true);
				menu.getItem(1).setEnabled(true);
				menu.getItem(2).setEnabled(true);
				menu.getItem(3).setEnabled(false);
			}
		} else {
			menu.getItem(0).setEnabled(false);
			menu.getItem(1).setEnabled(false);
			menu.getItem(2).setEnabled(false);
			menu.getItem(3).setEnabled(true);
			// menu.getItem(4).setEnabled(false);
		}
		return super.onPrepareOptionsMenu(menu);
	}

	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
		switch (item.getItemId()) {
		case MENU_DEFAULT_PATH:
			setDefaultPath();
			break;
		case MENU_ADD:
			FileUtil util = new FileUtil(this);
			util.createNewDir(currentFileString);
			break;
        case MENU_CD_ROM:
            if (hasCDROM) {
                try {
                    getMs().unmountVolume(CDROM_PATH, true, false);
                    hasCDROM = false;
                } catch (Exception e) {
                    Log.e(TAG, "Exception : " + e);
                }
            } else {
                Toast.makeText(this,
						getString(R.string.no_cdrom), Toast.LENGTH_LONG).show();
            }
			break;
		case MENU_SEARCH:
			searchFileDialog();
			break;
		case MENU_CUT:
			managerF(myPosition, MENU_CUT);
			break;
		case MENU_PASTE:
			managerF(myPosition, MENU_PASTE);
			break;
		case MENU_DELETE:
			managerF(myPosition, MENU_DELETE);
			break;
		case MENU_RENAME:
			managerF(myPosition, MENU_RENAME);
			break;
		case MENU_COPY:
			managerF(myPosition, MENU_COPY);
			break;
		case MENU_HELP:
			FileMenu.setHelpFlag(1);
			FileMenu.filterType(MainExplorerActivity.this, MENU_HELP, null);
			break;
		}
		return true;
	}

    IMountService getMs() {
        IBinder service = ServiceManager.getService("mount");
        if (service != null) {
            return IMountService.Stub.asInterface(service);
        } else {
            Log.e(TAG, "Can't get mount service");
        }
        return null;
    }

	private OnItemClickListener ItemClickListener = new OnItemClickListener() {

		public void onItemClick(AdapterView<?> l, View v, int position, long id) {
			if (listFile.size() > 0) {
				if (position >= listFile.size()) {
					position = listFile.size() - 1;
				}
				// chmod the file
				chmodFile(listFile.get(position).getPath());
				if (listFile.get(position).isDirectory()
						&& listFile.get(position).canRead()) {
					intList.add(position);
					clickPos = 0;
				} else {
					clickPos = position;
				}
				myPosition = clickPos;
				arrayFile.clear();
				arrayDir.clear();
				// broken into the directory contains many files,click again
				// error
				preCurrentPath = currentFileString;
				keyBack = false;
				getFiles(listFile.get(position).getPath());
			}
		}
	};

	private OnItemClickListener deleListener = new OnItemClickListener() {

		public void onItemClick(AdapterView<?> l, View v, int position, long id) {
			ControlListAdapter adapter = (ControlListAdapter) list.getAdapter();
			CheckedTextView check = (CheckedTextView) v
					.findViewById(R.id.check);
			String path = adapter.getList().get(position).getPath();
			if (check.isChecked()) {
				selectList.add(path);
			} else {
				selectList.remove(path);
			}
		}
	};

	/**
	 * Depending on the file directory path judgment do:
	 * Go to the directory the file: Open the file system application
	 * CNcomment:根据文件路径判断执行的操作 目录:进入目录 文件:系统应用打开文件
	 * @param path
	 */

	public void getFiles(String path) {
		if (path == null)
			return;
		openFile = new File(path);
		if (openFile.exists()) {
			if (openFile.isDirectory()) {
				if (mIsSupportBD) {
					if (FileUtil.getMIMEType(openFile, this).equals("video/bd")) {
						preCurrentPath = "";
						// currentFileString = path;
						intList.remove(intList.size() - 1);
						Intent intent = new Intent();
						intent.setClassName(
								"com.hisilicon.android.videoplayer",
								"com.hisilicon.android.videoplayer.activity.MediaFileListService");
						intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
						intent.setDataAndType(Uri.parse(path), "video/bd");
						intent.putExtra("sortCount", sortCount);
						intent.putExtra("isNetworkFile", isNetworkFile);
						startService(intent);
						return;
					}
                    else if (FileUtil.getMIMEType(openFile, this).equals("video/dvd")) {
						preCurrentPath = "";
						// currentFileString = path;
						intList.remove(intList.size() - 1);
						Intent intent = new Intent();
						intent.setClassName(
								"com.hisilicon.android.videoplayer",
								"com.hisilicon.android.videoplayer.activity.MediaFileListService");
						intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
						intent.setDataAndType(Uri.parse(path), "video/dvd");
						intent.putExtra("sortCount", sortCount);
						intent.putExtra("isNetworkFile", isNetworkFile);
						startService(intent);
						return;
					}
				}
				currentFileString = path;
				updateList(true);
			} else {
				super.openFile(this, openFile);
			}
		} else {
			refushList();
		}
	};

	/**
	 * Populate the list of files to the data container
	 * CNcomment:将文件列表填充到数据容器中
	 * @param files
	 * @param fileroot
	 */
	public void fill(File fileroot) {
		try {
			// li = adapter.getFiles();
			if (clickPos >= listFile.size()) {
				clickPos = listFile.size() - 1;
			}
			pathTxt.setText(fileroot.getPath());
			numInfo.setText("[" + (clickPos + 1) + "-" + listFile.size() + "]");
			if (!fileroot.getPath().equals(directorys)) {
				parentPath = fileroot.getParent();
				currentFileString = fileroot.getPath();
			} else {
				currentFileString = directorys;
			}

			if (listFile.size() == 0) {
				numInfo.setText("[" + 0 + "-" + 0 + "]");
			}

			/*
			 * if ((listFile.size() == 0) && (filterBut.findFocus() == null)) {
			 * sortBut.requestFocus(); }
			 */

			if (clickPos >= 0) {
				if (listView.getVisibility() == View.VISIBLE) {
					// listView.requestFocus();
					listView.setSelection(clickPos);
				} else if (gridView.getVisibility() == View.VISIBLE) {
					gridView.requestFocus();
					gridView.setSelection(clickPos);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void setDefaultPath() {
		File file = new File(currentFileString + "/"
				+ listFile.get(myPosition).getName());

		SharedPreferences p = getSharedPreferences("musicPath", 2);
		SharedPreferences.Editor editor = p.edit();
		if (file.isDirectory()) {
			editor.putString(MUSIC_PATH, file.getPath());
		} else {
			editor.putString(MUSIC_PATH, currentFileString);
		}
		editor.commit();
	}

	/**
	 * File Operations Management
	 * CNcomment:管理文件操作
	 * @param position
	 * @param item
	 */
	private void managerF(final int position, final int item) {

		// while first delete more than one file then cause exception
		// if(position == listFile.size()){
		if (position >= listFile.size()) {
			if (listFile.size() != 0) {
				myPosition = listFile.size() - 1;
			} else {
				myPosition = 0;
			}
		}

		menu_item = item;
		if (item == MENU_PASTE) {
				getMenu(myPosition, item, list);
            } else if (item == MENU_RENAME){
                LayoutInflater inflater = LayoutInflater
					.from(MainExplorerActivity.this);
                View view = inflater.inflate(R.layout.samba_server_list_dlg_layout,
					null);
				dialog = new NewCreateDialog(MainExplorerActivity.this);
				dialog.setView(view);
				dialog.setButton(DialogInterface.BUTTON_POSITIVE,
						getString(R.string.ok), imageButClick);
				dialog.setButton(DialogInterface.BUTTON_NEGATIVE,
						getString(R.string.cancel), imageButClick);
				dialog.show();
				dialog = FileUtil.setDialogParams(dialog,
						MainExplorerActivity.this);
				dialog.getButton(DialogInterface.BUTTON_POSITIVE)
						.setTextAppearance(MainExplorerActivity.this,
								android.R.style.TextAppearance_Large_Inverse);
				dialog.getButton(DialogInterface.BUTTON_POSITIVE)
						.requestFocus();
				dialog.getButton(DialogInterface.BUTTON_NEGATIVE)
						.setTextAppearance(MainExplorerActivity.this,
								android.R.style.TextAppearance_Large_Inverse);
				list = (ListView) dialog
						.findViewById(R.id.lvSambaServer);
				selectList.clear();
				list.setItemsCanFocus(false);
				list.setChoiceMode(ListView.CHOICE_MODE_SINGLE);
				list.setAdapter(new ControlListAdapter(MainExplorerActivity.this,
						listFile));
				list.setItemChecked(myPosition, true);
				list.setSelection(myPosition);
				selectList.add(listFile.get(myPosition).getPath());
				list.setOnItemClickListener(deleListener);
				dialog.getButton(DialogInterface.BUTTON_POSITIVE)
						.requestFocus();
		} else {
			LayoutInflater inflater = LayoutInflater
					.from(MainExplorerActivity.this);
			View view = inflater.inflate(R.layout.samba_server_list_dlg_layout,
					null);
			dialog = new NewCreateDialog(MainExplorerActivity.this);
			dialog.setView(view);
			dialog.setButton(DialogInterface.BUTTON_POSITIVE,
					getString(R.string.ok), imageButClick);
			dialog.setButton(DialogInterface.BUTTON_NEGATIVE,
					getString(R.string.cancel), imageButClick);
			dialog.show();
			list = (ListView) view.findViewById(R.id.lvSambaServer);
			dialog = FileUtil
					.setDialogParams(dialog, MainExplorerActivity.this);

			dialog.getButton(DialogInterface.BUTTON_POSITIVE)
					.setTextAppearance(MainExplorerActivity.this,
							android.R.style.TextAppearance_Large_Inverse);
			dialog.getButton(DialogInterface.BUTTON_POSITIVE).requestFocus();
			dialog.getButton(DialogInterface.BUTTON_NEGATIVE)
					.setTextAppearance(MainExplorerActivity.this,
							android.R.style.TextAppearance_Large_Inverse);

			// Make a list of multiple choice mode
			// CNcomment:让列表为多选模式
			list.setItemsCanFocus(false);
			list.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);
			selectList.clear();

			list.setAdapter(new ControlListAdapter(MainExplorerActivity.this,
					listFile));
			list.setItemChecked(myPosition, true);
			list.setSelection(myPosition);
			// list.setItemChecked(myPosition, true);
			// list.setSelection(myPosition);
			selectList.add(listFile.get(myPosition).getPath());
			list.setOnItemClickListener(deleListener);

			list.clearFocus();
			dialog.getButton(DialogInterface.BUTTON_POSITIVE).requestFocus();
		}
	}

	/**
	 * operation menu
	 * CNcomment:操作菜单
	 * @param position
	 *            CNcomment:目标文件位置
	 * @param item
	 *            CNcomment:操作
	 * @param list
	 *            CNcomment:数据容器
	 */
	private void getMenu(final int position, final int item, final ListView list) {
		int selectionRowID = (int) position;
		File file = null;
		File myFile = null;
		myFile = new File(currentFileString);
		FileMenu menu = new FileMenu();
		SharedPreferences sp = getSharedPreferences("OPERATE", SHARE_MODE);

		if (item == MENU_RENAME) {
			fileArray = new ArrayList<File>();
			//file = new File(currentFileString + "/"
					//+ listFile.get(selectionRowID).getName());
			for (int i = 0; i < selectList.size(); i++) {
				file = new File(selectList.get(i));
				fileArray.add(file);
			}
			fileArray.add(file);
			menu.getTaskMenuDialog(MainExplorerActivity.this, myFile, fileArray, sp,
					item, 0);
		} else if (item == MENU_PASTE) {
			fileArray = new ArrayList<File>();
			menu.getTaskMenuDialog(MainExplorerActivity.this, myFile,
					fileArray, sp, item, 1);
		} else {
			fileArray = new ArrayList<File>();
			for (int i = 0; i < selectList.size(); i++) {
				file = new File(selectList.get(i));
				fileArray.add(file);
			}
			menu.getTaskMenuDialog(MainExplorerActivity.this, myFile,
					fileArray, sp, item, 1);
		}

	}

	private Handler handler = new Handler() {
		public synchronized void handleMessage(Message msg) {
			switch (msg.what) {
			case SEARCH_RESULT:
				if (progress != null && progress.isShowing()) {
					progress.dismiss();
				}

				synchronized (lock) {
					if (arrayFile.size() == 0 && arrayDir.size() == 0) {
						FileUtil.showToast(MainExplorerActivity.this,
								getString(R.string.no_search_file));
						return;
					} else {
						updateList(true);
					}
				}
				break;
			case UPDATE_LIST:
				if (progress != null && progress.isShowing()) {
					progress.dismiss();
				}
				if (listView.getVisibility() == View.VISIBLE) {
					adapter = new FileAdapter(MainExplorerActivity.this,
							listFile, listlayout);
					listView.setAdapter(adapter);
					listView.setOnItemSelectedListener(itemSelect);
					listView.setOnItemClickListener(ItemClickListener);
				} else if (gridView.getVisibility() == View.VISIBLE) {
					adapter = new FileAdapter(MainExplorerActivity.this,
							listFile, gridlayout);
					gridView.setAdapter(adapter);
					gridView.setOnItemClickListener(ItemClickListener);
					gridView.setOnItemSelectedListener(itemSelect);
				}
				fill(new File(currentFileString));
				break;
			case ISO_MOUNT_SUCCESS:
				if (progress != null && progress.isShowing()) {
					progress.dismiss();
				}
				intList.add(myPosition);
				getFiles(mISOLoopPath);
				break;
			case ISO_MOUNT_FAILD:
				if (progress != null && progress.isShowing()) {
					progress.dismiss();
				}
				FileUtil.showToast(MainExplorerActivity.this,
						getString(R.string.new_mout_fail));
				break;
			case CHMOD_FILE:
				getMenu(myPosition, menu_item, list);
				break;
			}
		}
	};

	OnItemSelectedListener itemSelect = new OnItemSelectedListener() {

		public void onItemSelected(AdapterView<?> parent, View view,
				int position, long id) {
			// invisiable();
			if (parent.equals(listView) || parent.equals(gridView)) {
				myPosition = position;
			}
			numInfo.setText("[" + (position + 1) + "-" + listFile.size() + "]");
		}

		public void onNothingSelected(AdapterView<?> parent) {
		}
	};

	/**
	 * File list sorting
	 * CNcomment:文件列表排序
	 * @param sort
	 *            CNcomment:排序方式
	 */
	public void updateList(boolean flag) {

		if (flag) {
			// for broken into the directory contains many files,click again
			// error
			listFile.clear();
			Log.i(TAG, "updateList");
			// sortBut.setOnClickListener(clickListener);
			//filterBut.setOnClickListener(clickListener);

			if (progress != null && progress.isShowing()) {
				progress.dismiss();
			}

			progress = new ProgressDialog(MainExplorerActivity.this);
			progress.show();

			if (adapter != null) {
				adapter.notifyDataSetChanged();
			}
			waitThreadToIdle(thread);
			thread = new MyThread();
			thread.setStopRun(false);
			progress.setOnCancelListener(new OnCancelListener() {
				public void onCancel(DialogInterface arg0) {
					thread.setStopRun(true);
					if (keyBack) {
						intList.add(clickPos);
					} else {
						clickPos = myPosition;
						currentFileString = preCurrentPath;
						Log.v("\33[32m Main1", "onCancel" + currentFileString
								+ "\33[0m");
						intList.remove(intList.size() - 1);
					}
					FileUtil.showToast(MainExplorerActivity.this,
							getString(R.string.cause_anr));
				}
			});
			thread.start();
		} else {
			adapter.notifyDataSetChanged();
			fill(new File(currentFileString));
		}

	}

	/**
	 * Obtain a collection of files directory
	 * CNcomment:获得目录下文件集合
	 * @param path
	 */
	private void geDdirectory(String path) {
		directorys = path;
		parentPath = path;
		currentFileString = path;
	}

	DialogInterface.OnClickListener imageButClick = new DialogInterface.OnClickListener() {

		public void onClick(DialogInterface dialog, int which) {
			if (which == DialogInterface.BUTTON_POSITIVE) {
				if (selectList.size() > 0) {
					getMenu(myPosition, menu_item, list);
					dialog.cancel();
				} else {
					FileUtil.showToast(MainExplorerActivity.this,
							MainExplorerActivity.this
									.getString(R.string.select_file));
				}
			} else {
				dialog.cancel();
			}
		}
	};

	int clickPos = 0;

	public boolean onKeyDown(int keyCode, KeyEvent event) {
		Log.w(" = ", " = " + keyCode);
		switch (keyCode) {
		case KeyEvent.KEYCODE_ENTER:
		case KeyEvent.KEYCODE_DPAD_CENTER:
			super.onKeyDown(KeyEvent.KEYCODE_ENTER, event);
			return true;

		case KeyEvent.KEYCODE_BACK:// KEYCODE_BACK
			keyBack = true;
			String newName = pathTxt.getText().toString();
			// The current directory is the root directory
			// CNcomment:当前目录是根目录
			if (newName.equals("")) {
				clickCount++;
				if (clickCount == 1) {
					// not choice the srt file then quit the FileM
					// FileUtil.showToast(MainExplorerActivity.this,
					// getString(R.string.quit_app));
					if (getIntent().getBooleanExtra("subFlag", false)) {
						Intent intent = new Intent();
						intent.setClassName("com.huawei.activity",
								"com.huawei.activity.VideoActivity");
						intent.putExtra("path", "");
						intent.putExtra("pathFlag", false);
						startActivity(intent);
						finish();
					} else {
						FileUtil.showToast(MainExplorerActivity.this,
								getString(R.string.quit_app));
					}
				} else if (clickCount == 2) {
					// Empty the contents of the clipboard
					// CNcomment:清空剪贴板内容
					SharedPreferences share = getSharedPreferences("OPERATE",
							SHARE_MODE);
					share.edit().clear().commit();
					if (FileUtil.getToast() != null) {
						FileUtil.getToast().cancel();
					}
					onBackPressed();
				}
			} else {
				clickCount = 0;
				if (!currentFileString.equals(directorys)) {
					arrayDir.clear();
					arrayFile.clear();
					if (newName.equals(ISO_PATH)) {
						getFiles(prevPath);
					} else {
						getFiles(parentPath);
					}
				} else {
					pathTxt.setText("");
					numInfo.setText("");
					// sortBut.setOnClickListener(null);
					// sortBut.setImageResource(sortArray[0]);
					sortCount = 0;
					//filterBut.setOnClickListener(null);
					//filterBut.setImageResource(filterArray[0]);
					filterCount = 0;
					gridView.setVisibility(View.INVISIBLE);
					listView.setVisibility(View.INVISIBLE);
					expandableListView.setVisibility(View.VISIBLE);
					listFile.clear();
					getsdList();
				}
				// Click the location of the parent directory
				// CNcomment:点击的父目录位置
				int pos = -1;
				if (intList.size() <= 0) {
					groupPosition = 0;
					intList.add(0);
				}

				pos = intList.size() - 1;
				if (pos >= 0) {
					if (listView.getVisibility() == View.VISIBLE) {
						clickPos = intList.get(pos);
						myPosition = clickPos;
						intList.remove(pos);
					} else if (gridView.getVisibility() == View.VISIBLE) {
						clickPos = intList.get(pos);
						myPosition = clickPos;
						intList.remove(pos);
					} else if (expandableListView.getVisibility() == View.VISIBLE) {
						expandableListView.requestFocus();
						if (groupPosition < groupList.size()) {
							if (intList.get(pos) >= groupList
									.get(groupPosition).getChildList().size()) {
								expandableListView.setSelectedChild(
										groupPosition, 0, true);
							} else {
								expandableListView.setSelectedChild(
										groupPosition, intList.get(pos), true);
							}
						} else {
							groupPosition = 0;
							expandableListView.setSelectedChild(groupPosition,
									intList.get(pos), true);
						}
					}

				}
			}
			return true;
		case KeyEvent.KEYCODE_SEARCH: // search
			if (expandableListView.getVisibility() == View.INVISIBLE) {
				searchFileDialog();
			}
			return true;
		case KeyEvent.KEYCODE_INFO: // info
			if (expandableListView.getVisibility() == View.INVISIBLE) {
				FileUtil util = new FileUtil(this);
				if (listFile.size() < myPosition) {
					return true;
				}
				util.showFileInfo(listFile.get(myPosition));
			}
			return true;

		case KeyEvent.KEYCODE_PAGE_UP:
			super.onKeyDown(keyCode, event);
			break;

		case KeyEvent.KEYCODE_PAGE_DOWN:
			super.onKeyDown(keyCode, event);
			break;
		}
		return false;
	}

	public String getCurrentFileString() {
		return currentFileString;
	}

	protected void onResume() {
		super.onResume();

		// for grally3D delete the file, flush the data
		if (!currentFileString.equals("")
				&& preCurrentPath.equals(currentFileString)) {
			updateList(true);
		}
	}

	public ListView getListView() {
		return listView;
	}

	private void getMountEquipmentList() {
		String[] mountType = getResources().getStringArray(R.array.mountType);
		MountInfo info = new MountInfo(this);
		groupList = new ArrayList<GroupInfo>();
		childList = new ArrayList<Map<String, String>>();
		GroupInfo group = null;
		for (int j = 0; j < mountType.length; j++) {
			group = new GroupInfo();
			childList = new ArrayList<Map<String, String>>();
			for (int i = 0; i < info.index; i++) {
				if (info.type[i] == j) {
					if (info.path[i] != null && ( info.path[i].contains("/mnt")
                            || info.path[i].contains("/storage"))) {
						Map<String, String> map = new HashMap<String, String>();
						// map.put(MOUNT_DEV, info.dev[i]);
						map.put(MOUNT_TYPE, String.valueOf(info.type[i]));
						map.put(MOUNT_PATH, info.path[i]);
						// map.put(MOUNT_LABLE, info.label[i]);
						map.put(MOUNT_LABLE, "");
						map.put(MOUNT_NAME, info.partition[i]);
                        if (CDROM_PATH.equals(info.path[i])) {
                            Log.d(TAG, "------CDROM-----");
                            hasCDROM = true;
                        }
						childList.add(map);
					}
				}
			}
			if (childList.size() > 0) {
				group.setChildList(childList);
				group.setName(mountType[j]);
				groupList.add(group);
			}
		}
	}

	private BroadcastReceiver usbReceiver = new BroadcastReceiver() {

		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (action.equals(Intent.ACTION_MEDIA_MOUNTED)
					|| action.equals(Intent.ACTION_MEDIA_REMOVED)
					|| action.equals(Intent.ACTION_MEDIA_UNMOUNTED)) {
				mHandler.removeMessages(0);
				Message msg = new Message();
				msg.what = 0;
				mHandler.sendMessageDelayed(msg, 1000);
				if (!pathTxt.getText().toString().equals("")) {
					if (action.equals(Intent.ACTION_MEDIA_REMOVED)
							|| action.equals(Intent.ACTION_MEDIA_UNMOUNTED)) {
						FileUtil.showToast(context,
								getString(R.string.uninstall_equi));
					}
				} else if (action.equals(Intent.ACTION_MEDIA_MOUNTED))
					FileUtil.showToast(context,
							getString(R.string.install_equi));
			}
		}
	};

	Handler mHandler = new Handler() {
		public void handleMessage(Message msg) {
			// if (pathTxt.getText().toString().equals("")) {
			refushList();
			// }
			super.handleMessage(msg);
		}

	};

	private void refushList() {
		getMountEquipmentList();
		expandableListView.setVisibility(View.VISIBLE);
		listView.setVisibility(View.INVISIBLE);
		gridView.setVisibility(View.INVISIBLE);
		intList.clear();
		numInfo.setText("");
		pathTxt.setText("");
		ExpandAdapter adapter = new ExpandAdapter(MainExplorerActivity.this,
				groupList);
		expandableListView.setAdapter(adapter);
		for (int i = 0; i < groupList.size(); i++) {
			expandableListView.expandGroup(i);
		}
	}

	private void getUSB() {
		IntentFilter usbFilter = new IntentFilter();
		usbFilter.addAction(Intent.ACTION_UMS_DISCONNECTED);
		usbFilter.addAction(Intent.ACTION_MEDIA_MOUNTED);
		usbFilter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);
		usbFilter.addAction(Intent.ACTION_MEDIA_REMOVED);
		usbFilter.addDataScheme("file");
		registerReceiver(usbReceiver, usbFilter);
	}

	protected void onDestroy() {
		unregisterReceiver(usbReceiver);
		super.onDestroy();
	}

	// broken into the directory contains many files,click again error
	class MyThread extends MyThreadBase {
		public void run() {
			if (getFlag()) {
				setFlag(false);
				synchronized (lock) {
					util = new FileUtil(MainExplorerActivity.this, filterCount,
							arrayDir, arrayFile, currentFileString);
				}
			} else {
				util = new FileUtil(MainExplorerActivity.this, filterCount,
						currentFileString);
			}
			if (currentFileString.startsWith(ISO_PATH)) {
				listFile = util.getFiles(sortCount, "net");
			} else {
				listFile = util.getFiles(sortCount, "local");
			}
			if (getStopRun()) {
				if (keyBack) {
					if (pathTxt.getText().toString().equals(ISO_PATH)) {
						currentFileString = util.currentFilePath;
					}
				}
			} else {
				currentFileString = util.currentFilePath;
				handler.sendEmptyMessage(UPDATE_LIST);
			}
		}

		/**
		 * Blu-ray ISO file filter, for maximum video file
		 * CNcomment:过滤蓝光ISO文件，获取最大视频文件
		 */
		public File getMaxFile(List<File> listFile) {
			int temp = 0;
			for (int i = 0; i < listFile.size(); i++) {
				if (listFile.get(temp).length() <= listFile.get(i).length())
					temp = i;
			}
			return listFile.get(temp);
		}
	}

	public Handler getHandler() {
		return handler;
	}

	public void operateSearch(boolean b) {
		if (b) {
			for (int i = 0; i < fileArray.size(); i++) {
				listFile.remove(fileArray.get(i));
			}
		}
	}

	protected void onStop() {
		super.onStop();
		super.cancleToast();
	}

	public TextView getPathTxt() {
		return pathTxt;
	}

	private static IMountService getMountService() {
		IBinder service = ServiceManager.getService("mount");
		if (service != null) {
			return IMountService.Stub.asInterface(service);
		} else {
			Log.e(TAG, "Can't get mount service");
		}
		return null;
	}
}
