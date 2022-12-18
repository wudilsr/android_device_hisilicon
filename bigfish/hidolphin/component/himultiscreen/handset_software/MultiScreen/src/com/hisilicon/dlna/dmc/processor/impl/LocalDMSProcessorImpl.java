package com.hisilicon.dlna.dmc.processor.impl;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.Item;

import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;
import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.ContentTree;

public class LocalDMSProcessorImpl implements DMSProcessor {

	/**
	 * 浏览本地媒体文件
	 * @param objectID 媒体ID
	 * @param startIndex  起始位置
	 * @param maxResult 本次浏览最大量
	 * @param listener 回调
	 */
	@Override
	public void browse(String objectID, int startIndex, int maxResult, DMSProcessorListner listener) {
		executeBrowse(objectID, startIndex, maxResult, listener);
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	private void executeBrowse(final String objectID, final int startIndex, final int defaultMaxResult, final DMSProcessorListner listener) {

		int endIndex = startIndex + defaultMaxResult;
		
		try {
			Container container = ContentTree.getContainer(objectID);

			Map<String, List<? extends DIDLObject>> result = new HashMap<String, List<? extends DIDLObject>>();

			List<Container> containers = container.getContainers();
			List<Item> items = container.getItems();

			boolean haveNext = false;

			if (containers.size() > endIndex) {
				haveNext = true;
				containers = containers.subList(startIndex, endIndex);
			} else if (items.size() > endIndex) {
				haveNext = true;
				items = items.subList(startIndex, endIndex);
			} else if (items.size() + containers.size() > endIndex) {
				haveNext = true;
				items = items.subList(0, endIndex - containers.size());
			}

			result.put("Containers", containers);
			result.put("Items", items);

			listener.onBrowseComplete(objectID, haveNext, result);
		} catch (Exception ex) {
			listener.onBrowseFail(ex.getMessage());
		}
		
	}

	@Override
	public boolean back(List<String> traceID, int maxResult, DMSProcessorListner listener) {
		int traceSize = traceID.size();
		if (traceSize > 2) {
			String parentID = traceID.get(traceSize - 2);
			traceID.remove(traceID.size() - 1);
			browse(parentID, 0, maxResult, listener);
			return true;
		}
		return false;
	}

	@Override
	public void dispose() {
		// TODO Auto-generated method stub

	}

}
