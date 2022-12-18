package com.hisilicon.dlna.dmc.gui.browse.files;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.GridView;

import com.hisilicon.multiscreen.mybox.R;

public class FoldersActivity extends Activity{
	private GridView mGridView_Folders;
	private HashMap<String, List<FileNode>> folders;
	private List<FolderBean> folderBeans;
	private Context context;

	@SuppressWarnings("unchecked")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.dlna_dms_folders);
		//Get folders
		context = this;
		folders = FileData.mGruopMap;
		initView(); 
	}

	private void initView(){
		mGridView_Folders = (GridView)findViewById(R.id.other_folders_browsing);
		folderBeans = subGroupOfImage(folders);
		FolderAdapter adapter = new FolderAdapter(this, mGridView_Folders);
		adapter.addFolderBeans(folderBeans);
		mGridView_Folders.setAdapter(adapter);
		mGridView_Folders.setOnItemClickListener(new FolderItemClickListener());
	}
	
	private class FolderItemClickListener implements OnItemClickListener{

		@Override
		public void onItemClick(AdapterView<?> parent, View view, int position,
				long id) {
			// TODO Auto-generated method stub
//			FolderBean item = folderBeans.get(position);
			Intent intent = new Intent(context, FilesActivity.class);
			intent.putExtra("FolderTitle", folderBeans.get(position).getFolderName());
			context.startActivity(intent);
			
		}
		
	}

	/**
	 * 组装分组界面GridView的数据源，因为我们扫描手机的时候将图片信息放在HashMap中
	 * 所以需要遍历HashMap将数据组装成List
	 * 
	 * @param mGruopMap
	 * @return
	 */
	private List<FolderBean> subGroupOfImage(HashMap<String, List<FileNode>> mGruopMap){
		if(mGruopMap==null || mGruopMap.size() == 0){
			return null;
		}
		List<FolderBean> list = new ArrayList<FolderBean>();

		Iterator<Map.Entry<String, List<FileNode>>> it = mGruopMap.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry<String, List<FileNode>> entry = it.next();
			FolderBean mImageBean = new FolderBean();
			String key = entry.getKey();
			List<FileNode> value = entry.getValue();

			mImageBean.setFolderName(key);
			mImageBean.setFileCounts(value.size());
			mImageBean.setTopImagePath(value.get(0).getPictureNode().getPath());//获取该组的第一张图片
			list.add(mImageBean);
		}

		return list;

	}
	
	public void onBackClick(View view) {
		finish();
	}

}
