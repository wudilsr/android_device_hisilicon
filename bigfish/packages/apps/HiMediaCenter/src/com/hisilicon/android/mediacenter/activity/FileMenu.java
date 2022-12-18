package com.hisilicon.android.mediacenter.activity;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import android.content.Intent;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.DialogInterface.OnClickListener;
import android.content.SharedPreferences.Editor;
import android.graphics.Color;
import android.os.Handler;
import android.os.Message;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.CheckedTextView;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Toast;

import android.app.Activity;
import android.os.Bundle;
import android.net.Uri;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

import com.hisilicon.android.mediacenter.common.CommonActivity;
import com.hisilicon.android.mediacenter.common.FileUtil;
import com.hisilicon.android.mediacenter.common.NewCreateDialog;
import com.hisilicon.android.mediacenter.common.RemoveFilterAdapter;
import com.hisilicon.android.mediacenter.R;
import com.hisilicon.android.mediacenter.common.SocketClient;

/**
 * realization of the menu operation
 * CNcomment:实现菜单具体操作
 */

public class FileMenu {

	private Context mContext;

	// current page view
	// CNcomment:当前页面视图
	private View myView;

	private static EditText myEditText;

	protected final static int MENU_COPY = Menu.FIRST + 2;

	protected final static int MENU_CUT = Menu.FIRST + 3;

	protected final static int MENU_PASTE = Menu.FIRST + 4;

	protected final static int MENU_DELETE = Menu.FIRST + 5;

	protected final static int MENU_RENAME = Menu.FIRST + 6;

	// Add filtering audio
	// CNcomment:添加过滤音频
	protected final static int ADD_MENU_AUDIO = Menu.FIRST + 7;

	// Add filter video
	// CNcomment:添加过滤视频
	protected final static int ADD_MENU_VIDEO = Menu.FIRST + 8;

	// Add filter photo
	// CNcomment:添加过滤图片
	protected final static int ADD_MENU_IMAGE = Menu.FIRST + 9;

	// Delete filter audio
	// CNcomment:删除过滤音频
	protected final static int REMOVE_MENU_AUDIO = Menu.FIRST + 10;

	// Delete filter video
	// CNcomment:删除过滤视频
	protected final static int REMOVE_MENU_VIDEO = Menu.FIRST + 11;

	// Delete filter photo
	// CNcomment:删除过滤图片
	protected final static int REMOVE_MENU_IMAGE = Menu.FIRST + 12;

	protected final static int MENU_HELP = Menu.FIRST + 13;

	private static final String COPYFILE = "COPYFILE";

	private static final String COPYDIR = "COPYDIR";

	private static final String CUTFILE = "CUTFILE";

	private static final String CUTDIR = "CUTDIR";

	// selected file collection
	// CNcomment:选中的文件集合
	public List<File> file;

	// existing file list
	// CNcomment:已存在的文件列表
	public List<Map<String, Object>> existFile;

	// selected file path
	// CNcomment:选中的文件路径
	public static String selected;

	// Associated page
	// CNcomment:关联页面
	public static CommonActivity MA;

	// identifier of paste
	// CNcomment:粘贴标识符
	private int flag = 0;

	private String newFilePath;

	private File mySelFile;

	ProgressDialog proDialog;

	private static SharedPreferences sp;

	// filter type set
	// CNcomment:过滤类型集合
	static List<String> li;

	// deleted filter type set
	// CNcomment:删除的过滤类型集合
	static List<String> nameList;

	long fileLenght = 0;

	static int resultCode = 0;

	static AlertDialog alertDialog = null;

	// The original file, the new file collection
	// CNcomment:原文件、目标文件集合
	List<Map<String, File>> listMap;

	private static String oTag = "SourceFile";

	private static String nTag = "NewFile";

	List<File> dirList = null;

	int cutFile = 0;

	public static int helpFlag = 0;

	private int pasteFlag = 0;

	private SharedPreferences.Editor editor;
	private static boolean showFlag = true;

	private List<Map<String, String>> moveSameDirectory;

	/**
	 * Adding filter conditions
	 * CNcomment:添加过滤条件
	 * @param ctx
	 * @param item
	 * @param sps
	 */
	public static void filterType(CommonActivity ctx, final int item,
			SharedPreferences sps) {
		MA = ctx;
		sp = sps;
		switch (item) {
		case ADD_MENU_AUDIO:
			addFilterDialog(sps, 0);
			break;
		case ADD_MENU_VIDEO:
			addFilterDialog(sps, 1);
			break;
		case ADD_MENU_IMAGE:
			addFilterDialog(sps, 2);
			break;
		case REMOVE_MENU_AUDIO:
			removeFilterDialog(sps);
			break;
		case REMOVE_MENU_VIDEO:
			removeFilterDialog(sps);
			break;
		case REMOVE_MENU_IMAGE:
			removeFilterDialog(sps);
			break;
		case MENU_HELP:
			showHelp();
			break;
		}
	}

	/**
	 * File operation Dialog
	 * CNcomment:操作文件的Dialog
	 * @param ctx
	 * @param selFile
	 * @param selectedfile
	 * @param sps
	 * @param which
	 */
	int index = 0;

	public void getTaskMenuDialog(CommonActivity ctx, final File selFile,
			List<File> selectedfile, SharedPreferences sps, final int which,
			int pasteFlag) {
		MA = ctx;
		mContext = ctx;
		this.pasteFlag = pasteFlag;
		file = selectedfile;
		mySelFile = selFile;

		sp = sps;
		switch (which) {
		case MENU_COPY: {
			MA.isFileCut = false;
			SharedPreferences.Editor editor = sp.edit();
			editor.clear();
			editor.commit();
			editor.putString("operate", "copy");
			for (int i = 0; i < file.size(); i++) {
				// Copy the folder
				// CNcomment:复制文件夹
				if (file.get(i).isDirectory()) {
					editor.putString(COPYDIR + i, file.get(i).getPath());
					editor.putString(COPYFILE, null);
					editor.putString(CUTFILE, null);
					editor.putString(CUTDIR, null);
					editor.putInt("NUM", file.size());
					Log.v("log", file.get(i).getPath());
				}
				// copy file
				// CNcomment:复制文件
				else {
					editor.putString(COPYFILE + i, file.get(i).getPath());
					editor.putString(COPYDIR, null);
					editor.putString(CUTFILE, null);
					editor.putString(CUTDIR, null);
					editor.putInt("NUM", file.size());
				}
			}
			editor.commit();
			return;
		}
		// Cutting operation
		// CNcomment:剪切操作
		case MENU_CUT: {
			MA.isFileCut = true;
			SharedPreferences.Editor editor = sp.edit();
			editor.clear();
			editor.commit();
			editor.putString("operate", "cut");
			for (int i = 0; i < file.size(); i++) {
				// cut folder
				// CNcomment:剪切文件夹
				if (file.get(i).isDirectory()) {
					editor.putString(CUTDIR + i, file.get(i).getPath());
					editor.putString(COPYFILE, null);
					editor.putString(CUTFILE, null);
					editor.putString(COPYDIR, null);
					editor.putInt("NUM", file.size());
				}
				// cut file
				// CNcomment:剪切文件
				else {
					editor.putString(CUTFILE + i, file.get(i).getPath());
					editor.putString(COPYFILE, null);
					editor.putString(COPYDIR, null);
					editor.putString(CUTDIR, null);
					editor.putInt("NUM", file.size());
				}
			}
			editor.commit();
			return;
		}
		// Paste operations
		// CNcomment:粘贴操作
		case MENU_PASTE: {
			try {
				listMap = new ArrayList<Map<String, File>>();
				existFile = new ArrayList<Map<String, Object>>();
				nExistFile = new ArrayList<Map<String, Object>>();
				fileList = new ArrayList<Map<String, Object>>();
				moveSameDirectory = new ArrayList<Map<String, String>>();
				if (sp != null) {
					for (int i = 0; i < sp.getInt("NUM", 1); i++) {
						editor = sp.edit();
						if (sp.getString(COPYFILE + i, null) != null) {
							doPaste(sp, COPYFILE, "file", i);
						} else if (sp.getString(COPYDIR + i, null) != null) {
							doPaste(sp, COPYDIR, "dir", i);
						} else if (sp.getString(CUTFILE + i, null) != null) {
							doPaste(sp, CUTFILE, "file", i);
						} else if (sp.getString(CUTDIR + i, null) != null) {
							doPaste(sp, CUTDIR, "dir", i);
						}
					}
				}

				// The parent directory to the directory in paste
				// CNcomment:父目录向子目录中粘贴
				if (flag == -2) {
					FileUtil.showToast(MA, MA.getString(R.string.sub_dir));
					MA.updateList(false);
				} else if (pasteFlag == 1
						&& FileUtil.getSdcardSpace(fileLenght, MA.mountSdPath)) {
					FileUtil.showToast(MA,
							MA.getString(R.string.sdcard_no_capacity));
				} else {
					dirList = new ArrayList<File>();
					if (existFile.size() > 0) {
						pasteFiles();
					} else {
						fileList.addAll(nExistFile);
						for (int i = 0; i < fileList.size(); i++) {
							String operate = fileList.get(i).get("operate")
									.toString();
							File file = (File) fileList.get(i).get("file");
							int index = Integer.parseInt(fileList.get(i)
									.get("index").toString());
							if (operate.equals(COPYFILE)) {
								copyFile(file.getPath(), selFile.getPath());
							}
							else if (operate.equals(COPYDIR)) {
								copyDir(file.getPath(), selFile.getPath());
							}
							else if (operate.equals(CUTFILE)) {
								moveFile(file.getPath(), selFile.getPath());
								editor.putString(CUTFILE + index, null);
								editor.putInt("NUM", sp.getInt("NUM", 0) - 1);
								editor.commit();
							}
							else if (operate.equals(CUTDIR)) {
								dirList.add(file);
								moveDir(file.getPath(), selFile.getPath());
								editor.putString(CUTDIR + index, null);
								editor.putInt("NUM", sp.getInt("NUM", 0) - 1);
								editor.commit();
							}
						}
						proDialog = new ProgressDialog(MA);
						proDialog.setMessage(MA.getString(R.string.paste_str));
						proDialog.show();
						CopyThread copyThread = new CopyThread();
						copyThread.start();
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
				FileUtil.showToast(MA, MA.getString(R.string.paste_error));
			}
			return;
		}
		case MENU_DELETE: {
			StringBuilder builder = new StringBuilder();
			for (int i = 0; i < file.size(); i++) {
				String fi = file.get(i).getName();
				if (i == file.size() - 1) {
					builder.append(fi);
				} else {
					builder.append(fi).append(",");
				}

			}
			doDelete(builder.toString());

			return;
		}
		case MENU_RENAME: {
			modifyFileOrDir(file.get(file.size()-1));
			return;
		}
		}
	}

	private void doDelete(String str) {
		new AlertDialog.Builder(MA)
				.setTitle(MA.getString(R.string.notice))
				.setIcon(R.drawable.alert)
				.setMessage(MA.getString(R.string.ok_delete, str))
				.setPositiveButton(MA.getString(R.string.ok),
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
								proDialog = new ProgressDialog(MA);
								proDialog.show();
								DelThread delThread = new DelThread();
								delThread.start();
							}
						})
				.setNegativeButton(MA.getString(R.string.cancel),
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
							}
						}).create().show();
	}

	private boolean delFlag = true;

	class DelThread extends Thread {
		public void run() {

			for (int i = 0; i < file.size(); i++) {
				if (file.get(i).isDirectory()) {
					delFlag = delDir(file.get(i));
				} else {
					delFlag = delFile(file.get(i));
				}
				Log.v("log", file.get(i).getPath());
			}
			MA.operateSearch(delFlag);
			handler.sendEmptyMessage(3);
		}
	};

	/**
	 * Modify the file or folder name
	 * CNcomment:修改文件名或者文件夹名
	 * @param f
	 */
	private void modifyFileOrDir(File f) {
		final File f_old = f;
		LayoutInflater factory = LayoutInflater.from(MA);
		myView = factory.inflate(R.layout.rename_alert, null);
		myEditText = (EditText) myView.findViewById(R.id.rename_edit);
		myEditText.setText(f_old.getName());
		showFlag = true;
		myEditText.addTextChangedListener(splitWatcher);
		OnClickListener listenerFileEdit = new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				final String modName = myEditText.getText().toString();
				final String pFile = f_old.getParentFile().getPath() + "/";
				final String newPath = pFile + modName;
				Log.w("TAG", " = " + newPath);
				final File f_new = new File(newPath);
				if (f_new.exists()) {
					if (!modName.equals(f_old.getName())) {
						if (modName.equals("")) {
							FileUtil.showToast(MA,
									MA.getString(R.string.Rename_null, modName));
						} else {
							FileUtil.showToast(MA,
									MA.getString(R.string.your_file, modName));
						}

					} else {
						FileUtil.showToast(MA,
								MA.getString(R.string.name_no_update));
					}
				} else {
					doRename(f_old, f_new, modName);

				}
			};
		};
		AlertDialog renameDialog = new AlertDialog.Builder(MA).create();
		renameDialog.setView(myView);
		renameDialog.setButton(AlertDialog.BUTTON_POSITIVE,
				MA.getString(R.string.ok), listenerFileEdit);
		renameDialog.setButton(AlertDialog.BUTTON_NEGATIVE,
				MA.getString(R.string.cancel),
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
					}
				});
		renameDialog.show();
	}

	private void doRename(final File f_old, final File f_new, String modName) {
		String str = (f_old.isDirectory() ? MA.getResources().getString(
				R.string.dir) : MA.getResources().getString(R.string.file));
		// Change confirmation
		// CNcomment:更改确认信息
		new AlertDialog.Builder(MA)
				.setTitle(MA.getResources().getString(R.string.notice))
				.setIcon(R.drawable.alert)
				.setMessage(
						MA.getString(R.string.ok_update, str, f_old.getName(),
								modName))
				.setPositiveButton(MA.getString(R.string.ok),
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
								if (f_old.renameTo(f_new)) {
									MA.updateList(true);
									FileUtil.showToast(MA, MA
											.getString(R.string.update_name_ok));
									if (f_old.getPath().contains("/mnt/nand")
											|| f_old.getPath().contains(
													"/mnt/sd")) {
										Uri uri = Uri.parse("file://"
												+ f_old.getParent());
										Intent intent = new Intent(
												"MEDIA_SCANNER_DESIGNATED_PATH",
												uri);
										// mContext.sendBroadcast(new
										// Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE,uri));
										intent.putExtra("scan", true);
										mContext.sendBroadcast(intent);
										Log.i("FileMenu",
												"rename file-------------f_old="
														+ f_old.getParent()
														+ " f_new="
														+ f_new.getPath());
									}
								} else {
									FileUtil.showToast(
											MA,
											MA.getString(R.string.update_name_error));
								}
							}
						})
				.setNegativeButton(
						MA.getResources().getString(R.string.cancel),
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
							}
						}).show();
	}

	/**
	 * copy File
	 * CNcomment:复制单个文件
	 * @param oldPath
	 * @param newPath
	 * @return boolean
	 */
	public boolean copyFile(String oldPath, String newPath) {
		try {
			String f_new = "";
			File f_old = new File(oldPath);
			if (newPath.endsWith(File.separator)) {
				f_new = newPath + f_old.getName();
			} else {
				f_new = newPath + File.separator + f_old.getName();
			}
			newFilePath = f_new;
			// for self-cover, the size is 0
			if (!f_new.equals(oldPath)) {
				Map<String, File> map = new HashMap<String, File>();
				map.put(oTag, f_old);
				map.put(nTag, new File(f_new));
				listMap.add(map);
			}
			return true;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	private void pasteFiles() {
		AlertDialog.Builder builder = new AlertDialog.Builder(MA);
		builder.setTitle(R.string.notice);
		builder.setIcon(R.drawable.alert).setMessage(
				MA.getString(R.string.override_file,
						((File) existFile.get(index).get("file")).getName()));
		builder.setPositiveButton(MA.getString(R.string.ok),
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						Editor editor = sp.edit();
						int num = sp.getInt("NUM", -1);
						fileList.add(existFile.get(index));
						if (nExistFile.size() > 0) {
							fileList.addAll(nExistFile);
						}
						index++;
						if (index < existFile.size()) {
							pasteFiles();
						} else {
							for (int i = 0; i < fileList.size(); i++) {
								String operate = fileList.get(i).get("operate")
										.toString();
								File file = (File) fileList.get(i).get("file");
								int index = Integer.parseInt(fileList.get(i)
										.get("index").toString());
								if (operate.equals(COPYFILE)) {
									copyFile(file.getPath(),
											mySelFile.getPath());
								} else if (operate.equals(COPYDIR)) {
									copyDir(file.getPath(), mySelFile.getPath());
								} else if (operate.equals(CUTFILE)) {
									moveFile(file.getPath(),
											mySelFile.getPath());
									editor.putString(CUTFILE + index, null);
									editor.putInt("NUM", num - 1);
									editor.commit();
								} else if (operate.equals(CUTDIR)) {
									dirList.add(file);
									moveDir(file.getPath(), mySelFile.getPath());
									editor.putString(CUTDIR + index, null);
									editor.putInt("NUM", num - 1);
									editor.commit();
								}
							}
							proDialog = new ProgressDialog(MA);
							proDialog.setMessage(MA
									.getString(R.string.paste_str));
							proDialog.show();
							CopyThread copyThread = new CopyThread();
							copyThread.start();
						}
					}
				});
		builder.setNegativeButton(MA.getString(R.string.cancel),
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						Editor editor = sp.edit();
						int num = sp.getInt("NUM", -1);

						if (nExistFile.size() > 0) {
							fileList.addAll(nExistFile);
						}

						index++;
						if (index < existFile.size()) {
							pasteFiles();
						} else {
							for (int i = 0; i < fileList.size(); i++) {
								String operate = fileList.get(i).get("operate")
										.toString();
								File file = (File) fileList.get(i).get("file");
								int index = Integer.parseInt(fileList.get(i)
										.get("index").toString());
								if (operate.equals(COPYFILE)) {
									copyFile(file.getPath(),
											mySelFile.getPath());
								} else if (operate.equals(COPYDIR)) {
									copyDir(file.getPath(), mySelFile.getPath());
								} else if (operate.equals(CUTFILE)) {
									moveFile(file.getPath(),
											mySelFile.getPath());
									editor.putString(CUTFILE + index, null);
									editor.putInt("NUM", num - 1);
									editor.commit();
								} else if (operate.equals(CUTDIR)) {
									dirList.add(file);
									moveDir(file.getPath(), mySelFile.getPath());
									editor.putString(CUTDIR + index, null);
									editor.putInt("NUM", num - 1);
									editor.commit();
								}
							}
							if (fileList.size() > 0) {
								proDialog = new ProgressDialog(MA);
								proDialog.setMessage(MA
										.getString(R.string.paste_str));
								proDialog.show();
								CopyThread copyThread = new CopyThread();
								copyThread.start();
							}
						}
					}
				}).show();
	}

	class CopyThread extends Thread {
		public void run() {

			File f1 = null;
			File f2 = null;
			FileInputStream in = null;
			FileOutputStream out = null;
			int length = 1024 * 1024;
			FileChannel inc = null;
			FileChannel outc = null;
			try {
				// for results inconsistent with the actual shear
				if (listMap.size() == 0) {
					// cut the file in the same mount directory or device
					// CNcomment:同一挂载目录或者设备中文件剪切
					if (moveSameDirectory.size() > 0) {
						int resultCode = 0;
						for (int i = 0; i < moveSameDirectory.size(); i++) {
							f1 = new File(moveSameDirectory.get(i).get(oTag));
							f2 = new File(moveSameDirectory.get(i).get(nTag));
							// moveFiles(moveSameDirectory.get(i).get(oTag),
							// moveSameDirectory.get(i).get(nTag));
							resultCode = moveFiles(moveSameDirectory.get(i)
									.get(oTag),
									moveSameDirectory.get(i).get(nTag));
							if (resultCode == 0) {
								continue;
							} else {
								moveSameDirectory.clear();
								handler.sendEmptyMessage(2);
								return;
							}
						}
						moveSameDirectory.clear();
						handler.sendEmptyMessage(1);
					} else {
						// paste empty folder
						// CNcomment:空文件夹粘贴
						for (File file : dirList) {
							delDir(file);
						}
						handler.sendEmptyMessage(1);
					}
					if (f2 != null
							&& (f2.getPath().contains("/mnt/nand") || f2
									.getPath().contains("/mnt/sd"))) {
						Uri uri_1 = Uri.parse("file://" + f1.getParent());
						Intent intent_1 = new Intent(
								"MEDIA_SCANNER_DESIGNATED_PATH", uri_1);
						intent_1.putExtra("scan", true);

						Uri uri_2 = Uri.parse("file://" + f2.getParent());
						Intent intent_2 = new Intent(
								"MEDIA_SCANNER_DESIGNATED_PATH", uri_2);
						intent_2.putExtra("scan", true);
						if (mContext != null) {
							mContext.sendBroadcast(intent_1);
							mContext.sendBroadcast(intent_2);
							Log.i("FileMenu",
									"paste file-------------f1="
											+ f1.getParent() + " f2="
											+ f2.getPath());
						}
					}
				} else {
					// paste file
					// CNcomment:文件粘贴
					for (int i = 0; i < listMap.size(); i++) {
						f1 = listMap.get(i).get(oTag);
						Log.w("IN", "INPUT");
						f2 = listMap.get(i).get(nTag);
            try{
                  int byteread = 0;
                  File newfile = new File(f2.getPath());
                  if (!newfile.exists()){
                        newfile.createNewFile();
                        InputStream inStream = new FileInputStream(f1.getPath());
                        FileOutputStream fs = new FileOutputStream(f2.getPath());
                        byte[] buffer = new byte[1024];
                        while ( (byteread = inStream.read(buffer)) != -1){
                            fs.write(buffer, 0, byteread);
                        }
                             inStream.close();
                             fs.close();
                   }
                }catch(Exception e){
                        e.printStackTrace();
                }
						if (cutFile == -1) {
							delFile(listMap.get(i).get(oTag));
						}
						if (i == listMap.size() - 1) {
							for (File file : dirList) {
								delDir(file);
							}
							handler.sendEmptyMessage(1);
						}
					}
					return;
				}
			} catch (Exception e) {
				Log.d("Exception", "E " + e);
				e.printStackTrace();
				handler.sendEmptyMessage(2);
				return;
			} finally {
				if (inc != null)
					if (inc.isOpen())
						try {
							inc.close();
						} catch (IOException e) {
							e.printStackTrace();
						}
				if (outc != null)
					try {
						outc.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				if (in != null)
					try {
						in.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				if (out != null) {
					try {
						out.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}

		}
	};

	/**
	 * cut the file in the same mount directory or device
	 * CNcomment:同一挂载或者设备目录下剪切文件
	 * @param oldPath
	 * @param newPath
	 * @return
	 */
	private int moveFiles(String oldPath, String newPath) {
		// for get the result of the mv command
		int resultCode = 0;
		try {
			// Runtime.getRuntime().exec(new String[]{"mv", oldPath,
			// newPath}).waitFor();
			resultCode = Runtime.getRuntime()
					.exec(new String[] { "mv", oldPath, newPath }).waitFor();
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
		Log.w("RESULTCODE", " = " + resultCode);
		return resultCode;
	}

	/**
	 * @param oldPath
	 * @param newPath
	 * @return boolean
	 */
	public boolean copyDir(String oldPath, String newPath) {
		boolean ret = true;
		try {
			File f_old = new File(oldPath);
			String d_old = "";
			String d_new = newPath + File.separator + f_old.getName();
			newFilePath = d_new;
			if (oldPath.equals(newPath)) {
				ret = false;
			} else {
				File f_new = new File(d_new);
				f_new.mkdirs();
				CommonActivity.chmodFile(f_new.getPath());
				File[] files = f_old.listFiles();
				for (int i = 0; i < files.length; i++) {
					d_old = oldPath + File.separator + files[i].getName();
					if (files[i].isFile()) {
						copyFile(d_old, d_new);
					} else {
						copyDir(d_old, d_new);
					}
				}
				ret = true;
			}
		} catch (Exception e) {
			e.printStackTrace();
			ret = false;
		}
		return ret;
	}

	/**
	 * cut and paste files in to the specified directory
	 * CNcomment:剪切并粘贴文件到指定目录
	 * @param oldPath
	 * @param newPath
	 */
	public boolean moveFile(String oldPath, String newPath) {
		boolean ret = false;
		try {
			if (oldPath.startsWith(MA.mountSdPath)
					&& newPath.startsWith(MA.mountSdPath)) {
				Map<String, String> map = new HashMap<String, String>();
				map.put(oTag, oldPath);
				map.put(nTag, newPath);
				newFilePath = newPath;
				moveSameDirectory.add(map);
			} else {
				cutFile = -1;
				copyFile(oldPath, newPath);
			}
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return ret;
	}

	/**
	 * cut and paste folder in to the specified directory
	 * CNcomment:剪切并粘贴文件夹到指定目录
	 * @param oldPath
	 * @param newPath
	 */
	public boolean moveDir(String oldPath, String newPath) {
		boolean ret = false;
		try {
			if (oldPath.startsWith(MA.mountSdPath)
					&& newPath.startsWith(MA.mountSdPath)) {
				Map<String, String> map = new HashMap<String, String>();
				map.put(oTag, oldPath);
				map.put(nTag, newPath);
				newFilePath = newPath;
				moveSameDirectory.add(map);
			} else {
				copyDir(oldPath, newPath);
			}
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return ret;
	}

	/**
	 * delete file
	 * CNcomment:删除单个文件
	 * @param file
	 * @return
	 */
	public boolean delFile(File f) {
		boolean ret = false;
		try {
			if (f.exists()) {
				f.delete();
				if (f.exists()) {
					ret = false;
				} else {
					ret = true;
					if (f.getPath().contains("/mnt/nand")
							|| f.getPath().contains("/mnt/sd")) {
						Uri uri_media = Uri.parse("file://" + f.getPath());
						Intent intent_media = new Intent(
								"MEDIA_SCANNER_MEDIA_PATH", uri_media);
						mContext.sendBroadcast(intent_media);
						Uri uri = Uri.parse("file://" + f.getParent());
						Intent intent = new Intent(
								"MEDIA_SCANNER_DESIGNATED_PATH", uri);
						intent.putExtra("scan", true);
						mContext.sendBroadcast(intent);
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return ret;
	}

	/**
	 * delete folder
	 * CNcomment:删除文件夹
	 * @param file
	 * @return
	 */
	public boolean delDir(File f) {
		boolean ret = false;
		try {
			if (f.exists()) {
				File[] files = f.listFiles();
				for (int i = 0; i < files.length; i++) {
					if (files[i].isDirectory()) {
						if (!delDir(files[i])) {
							return false;
						}
					} else {
						files[i].delete();
						if (files[i].exists()) {
							return false;
						}
					}
				}
				ret = f.delete();
			}
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return ret;
	}

	/**
	 * @param sp
	 * @param operate
	 * @param type
	 * @param i
	 */
	// boolean existFlag = false;
	List<Map<String, Object>> fileList;
	List<Map<String, Object>> nExistFile;

	public void doPaste(SharedPreferences sp, String operate, String type, int i) {
		Map<String, Object> existMap = null;
		selected = sp.getString(operate + i, null);
		File f = new File(selected);
		if (pasteFlag == 1) {
			if (f.isDirectory()) {
				fileLenght += FileUtil.getDirSize(f);
			} else {
				fileLenght += f.length();
			}
		}

		String filenameString = f.getName();
		File fnew = new File(mySelFile + "/" + filenameString);

		/**
		 * The file or folder already exists
		 * CNcomment:文件或者文件夹已存在时
		 */
		// paste the same file
		// CNcomment:同一文件粘贴
		if (fnew.equals(f)) {
			existMap = new HashMap<String, Object>();
			existMap.put("file", new File(selected));
			existMap.put("type", type);
			existMap.put("index", i);
			existMap.put("operate", operate);
			existFile.add(existMap);
			return;
		}

		// paste the same folder
		// CNcomment:父子目录粘贴
		if (f.isDirectory()) {
			if (fnew.getPath().length() > f.getPath().length()) {
				if (fnew.getPath().startsWith(f.getPath() + "/")) {
					flag = -2;
					return;
				}
			}
		}

		if (fnew.exists()) {
			existMap = new HashMap<String, Object>();
			existMap.put("file", new File(selected));
			existMap.put("type", type);
			existMap.put("index", i);
			existMap.put("operate", operate);
			existFile.add(existMap);
		} else {
			existMap = new HashMap<String, Object>();
			existMap.put("file", new File(selected));
			existMap.put("type", type);
			existMap.put("index", i);
			existMap.put("operate", operate);
			nExistFile.add(existMap);
		}
	}

	/**
	 * add filters
	 * CNcomment:添加过滤
	 * @param sp
	 */
	private static void addFilterDialog(final SharedPreferences sp, int flag) {

		String type = "";
		if (flag == 0) {
			type = MA.getString(R.string.music);
		} else if (flag == 1) {
			type = MA.getString(R.string.video);
		} else if (flag == 2) {
			type = MA.getString(R.string.image);
		}

		StringBuilder builder = new StringBuilder();
		Iterator<?> it = sp.getAll().values().iterator();
		builder.append("\n");
		int i = 0;
		while (it.hasNext()) {
			i++;
			if (i == sp.getAll().size()) {
				builder.append(it.next().toString());
			} else {
				builder.append(it.next().toString()).append(", ");
			}
		}
		LayoutInflater factory = LayoutInflater.from(MA);
		View myView = factory.inflate(R.layout.add_filter, null);
		alertDialog = new NewCreateDialog(MA);
		alertDialog.setView(myView);
		alertDialog.setButton(DialogInterface.BUTTON_POSITIVE,
				MA.getString(R.string.ok), clickListener);
		alertDialog.setButton(DialogInterface.BUTTON_NEGATIVE,
				MA.getString(R.string.cancel), clickListener);
		alertDialog.show();
		alertDialog.getButton(DialogInterface.BUTTON_POSITIVE)
				.setTextAppearance(MA,
						android.R.style.TextAppearance_Large_Inverse);
		alertDialog.getButton(DialogInterface.BUTTON_NEGATIVE)
				.setTextAppearance(MA,
						android.R.style.TextAppearance_Large_Inverse);

		myEditText = (EditText) alertDialog.findViewById(R.id.add_filter);
		showFlag = false;
		myEditText.addTextChangedListener(splitWatcher);
		TextView text = (TextView) alertDialog.findViewById(R.id.list);
		text.setText(MA.getString(R.string.hold_type, type, builder.toString())
				.toUpperCase());
		text.setTextAppearance(MA, android.R.style.TextAppearance_Large_Inverse);
		text.setTextColor(Color.WHITE);
		myEditText.requestFocus();
	}

	/**
	 * delete filters
	 * CNcomment:删除过滤条件
	 * 
	 * @param sp
	 */
	private static void removeFilterDialog(final SharedPreferences sp) {
		final SharedPreferences share = sp;
		final SharedPreferences.Editor editor = sp.edit();
		nameList = new ArrayList<String>();
		li = new ArrayList<String>();
		Iterator<?> it = share.getAll().values().iterator();
		while (it.hasNext()) {
			li.add((String) it.next());
		}
		if (li.size() > 0) {
			LayoutInflater factory = LayoutInflater.from(MA);
			View myView = factory.inflate(R.layout.remove_filter, null);
			alertDialog = new NewCreateDialog(MA);
			alertDialog.setView(myView);
			alertDialog.setButton(DialogInterface.BUTTON_POSITIVE,
					MA.getString(R.string.ok), new OnClickListener() {
						public void onClick(DialogInterface dialog, int which) {
							if (nameList.size() > 0) {
								int flag = 0;
								String str = "";
								for (int i = 0; i < nameList.size(); i++) {
									if (nameList.get(i).equals("mp3")
											|| nameList.get(i).equals("jpg")
											|| nameList.get(i).equals("bmp")
											|| nameList.get(i).equals("gif")
											|| nameList.get(i).equals("mp4")
											|| nameList.get(i).equals("3gp")) {
										flag = 1;
										str = nameList.get(i);
										break;
									} else {
										editor.remove(nameList.get(i));
										editor.commit();
										alertDialog.dismiss();
										MA.updateList(true);
									}
								}

								if (flag == 1) {
									FileUtil.showToast(MA, MA.getString(
											R.string.type_undelete, str));
								} else {
									FileUtil.showToast(MA,
											MA.getString(R.string.delete_v));
								}

							} else {
								FileUtil.showToast(MA,
										MA.getString(R.string.select_type));
							}
						}
					});
			alertDialog.setButton(DialogInterface.BUTTON_NEGATIVE,
					MA.getString(R.string.cancel), new OnClickListener() {
						public void onClick(DialogInterface dialog, int which) {
							alertDialog.dismiss();
						}
					});
			alertDialog.show();
			alertDialog.getButton(DialogInterface.BUTTON_POSITIVE)
					.setTextAppearance(MA,
							android.R.style.TextAppearance_Large_Inverse);
			alertDialog.getButton(DialogInterface.BUTTON_NEGATIVE)
					.setTextAppearance(MA,
							android.R.style.TextAppearance_Large_Inverse);
			ListView list = (ListView) alertDialog.findViewById(R.id.list);
			list.setItemsCanFocus(false);
			list.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);
			RemoveFilterAdapter adapter = new RemoveFilterAdapter(MA, li);
			list.setAdapter(adapter);
			list.setOnItemClickListener(deleListener);
		}
	}

	private static OnItemClickListener deleListener = new OnItemClickListener() {

		public void onItemClick(AdapterView<?> l, View v, int position, long id) {
			CheckedTextView check = (CheckedTextView) v
					.findViewById(R.id.check);
			if (check.isChecked()) {
				nameList.remove(li.get(position));
				check.setChecked(false);
			} else {
				nameList.add(li.get(position));
				check.setChecked(true);
			}
		}
	};

	private static void showHelp() {
		try {
			InputStream is = null;
			Log.w("FLAG", " = " + helpFlag);
			if (helpFlag == 1) {
				is = MA.getResources().openRawResource(R.raw.help_local);
			} else if (helpFlag == 2) {
				is = MA.getResources().openRawResource(R.raw.help_samba);
			} else {
				is = MA.getResources().openRawResource(R.raw.help_nfs);
			}
			StringBuffer buffer = new StringBuffer();
			buffer.append("\n");
			byte[] b = new byte[is.available()];
			do {
				int count = is.read(b);
				if (count < 0) {
					break;
				}
				String str = new String(b, 0, count, "utf-8");
				buffer.append(str);
			} while (true);
			is.close();
			LayoutInflater factory = LayoutInflater.from(MA);
			View myView = factory.inflate(R.layout.help, null);
			TextView textView = (TextView) myView.findViewById(R.id.help_text);
			textView.setText(buffer.toString());
			new AlertDialog.Builder(MA).setView(myView)
					.setPositiveButton(MA.getString(R.string.close), null)
					.create().show();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private Handler handler = new Handler() {
		public void handleMessage(Message mes) {

			if (proDialog != null && proDialog.isShowing()) {
				proDialog.dismiss();
                Toast.makeText(mContext, R.string.running_background, Toast.LENGTH_SHORT).show();
			}

			if (mes.what == 1) {
				if (new File(selected).exists()
						&& sp.getString("operate", "").equals("cut")
						&& !new File(newFilePath).exists()) {
					FileUtil.showToast(MA, MA.getString(R.string.paste_error));
				} else if (!new File(newFilePath).exists()) {
					FileUtil.showToast(MA, MA.getString(R.string.paste_error));
				} else {
					if (sp.getString("operate", "").equals("cut")) {
						sp.edit().clear().commit();
					}
					FileUtil.showToast(MA, MA.getString(R.string.paste_v));
					MA.updateList(true);
				}
			} else if (mes.what == 2) {
				FileUtil.showToast(MA, MA.getString(R.string.paste_error));
			} else if (mes.what == 3) {
				if (delFlag) {
					FileUtil.showToast(MA, MA.getString(R.string.delete_v));
				} else {
					FileUtil.showToast(MA, MA.getString(R.string.delete_error));
				}
				MA.updateList(false);
			} else if (mes.what == 4) {
				MA.updateList(true);
			}
			try {
				String command_chmod = "sync";
				Runtime runtime = Runtime.getRuntime();
				runtime.exec(command_chmod);
			} catch (IOException e) {
				Log.w("TAG", " = " + e);
				e.printStackTrace();
			}
		}
	};

	/**
	 * Add the input box to input limit filter type
	 * CNcomment:添加过滤类型输入框输入限制
	 */
	static TextWatcher splitWatcher = new TextWatcher() {

		int tempLength = 0;
		int Num = 0;

		public void onTextChanged(CharSequence s, int start, int before,
				int count) {

		}

		public void beforeTextChanged(CharSequence s, int start, int count,
				int after) {
			tempLength = s.length();
			Num = start;
		}

		public void afterTextChanged(Editable s) {
			try {
				int len = s.toString().getBytes("GBK").length;
				if (s.length() > tempLength) {
					if (s.charAt(Num) == '/' || s.charAt(Num) == '\\'
							|| s.charAt(Num) == ':' || s.charAt(Num) == '*'
							|| s.charAt(Num) == '?' || s.charAt(Num) == '\"'
							|| s.charAt(Num) == '<' || s.charAt(Num) == '>'
							|| s.charAt(Num) == '|') {
						s.delete(Num, Num + 1);
						if (showFlag) {
							FileUtil.showToast(MA,
									MA.getString(R.string.name_falid));
						} else {
							FileUtil.showToast(MA,
									MA.getString(R.string.suffix_falid));
						}
					} else if (showFlag) {
						if (len > 128) {
							s.delete(Num, Num + 1);
							FileUtil.showToast(MA,
									MA.getString(R.string.name_long));
						}
					} else {
						if (s.length() > 10) {
							s.delete(Num, Num + 1);
							FileUtil.showToast(MA,
									MA.getString(R.string.suffix_long));
						}
					}
				}
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}
		}
	};

	/**
	 * Add filter type operation
	 * CNcomment:添加过滤类型操作
	 */
	static DialogInterface.OnClickListener clickListener = new DialogInterface.OnClickListener() {
		public void onClick(DialogInterface dialog, int which) {
			if (which == DialogInterface.BUTTON_POSITIVE) {
				Editor editor = sp.edit();

				if (myEditText.getText().toString().equals("")) {
					FileUtil.showToast(MA, MA.getString(R.string.suffix_no));
				}
				else if (hasFilterExist(myEditText.getText().toString()
						.toUpperCase())) {
					FileUtil.showToast(MA, MA.getString(R.string.suffix_exist));

				}
				else {
					editor.putString(myEditText.getText().toString()
							.toUpperCase(), myEditText.getText().toString()
							.toUpperCase());
					editor.commit();
					FileUtil.showToast(MA, MA.getString(R.string.add_ok));
					alertDialog.dismiss();
					MA.updateList(true);
				}
			} else {
				alertDialog.dismiss();
			}
		}
	};

	/**
	 * Determine the filter conditions exists
	 * CNcomment:判断过滤条件是否存在
	 * @param filter
	 * @return
	 */
	private static boolean hasFilterExist(String filter) {
		SharedPreferences shareAudio = MA.getSharedPreferences("AUDIO",
				Context.MODE_WORLD_READABLE);
		String strAudio = shareAudio.getString(filter, "");
		SharedPreferences shareVideo = MA.getSharedPreferences("VIDEO",
				Context.MODE_WORLD_READABLE);
		String strVideo = shareVideo.getString(filter, "");
		SharedPreferences shareImage = MA.getSharedPreferences("IMAGE",
				Context.MODE_WORLD_READABLE);
		String strImage = shareImage.getString(filter, "");

		if (strAudio.equals("") && strVideo.equals("") && strImage.equals("")) {
			return false;
		} else {
			return true;
		}
	}

	public static void setHelpFlag(int flag) {
		helpFlag = flag;
	}
}
