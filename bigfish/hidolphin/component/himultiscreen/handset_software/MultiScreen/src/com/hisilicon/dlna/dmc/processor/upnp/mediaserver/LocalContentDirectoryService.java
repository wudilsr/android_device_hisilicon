package com.hisilicon.dlna.dmc.processor.upnp.mediaserver;

import java.util.List;

import org.teleal.cling.support.contentdirectory.AbstractContentDirectoryService;
import org.teleal.cling.support.contentdirectory.ContentDirectoryErrorCode;
import org.teleal.cling.support.contentdirectory.ContentDirectoryException;
import org.teleal.cling.support.contentdirectory.DIDLParser;
import org.teleal.cling.support.model.BrowseFlag;
import org.teleal.cling.support.model.BrowseResult;
import org.teleal.cling.support.model.DIDLContent;
import org.teleal.cling.support.model.SortCriterion;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.Item;

import android.util.Log;

public class LocalContentDirectoryService extends AbstractContentDirectoryService {

	private final static String LOGTAG = LocalContentDirectoryService.class.getSimpleName();

	/**
	 * isShare = false 其他DMS不可浏览该设备媒体
	 */
	@Override
	public BrowseResult browse(String objectID, BrowseFlag browseFlag,
			String filter, long firstResult, long maxResults,
			SortCriterion[] orderby) throws ContentDirectoryException {
		try {
			DIDLContent didlContent = new DIDLContent();
			boolean isShare = false;
			if (!isShare)
				return new BrowseResult(new DIDLParser().generate(didlContent), 0, 0);
			
			ContentNode contentNode = ContentTree.getNode(objectID);
			Log.v(LOGTAG, "someone's browsing id: " + objectID);

			if (contentNode == null)
				return new BrowseResult(new DIDLParser().generate(didlContent), 0, 0);

			if (contentNode.isItem()) {
				didlContent.addItem(contentNode.getItem());
				Log.v(LOGTAG, "returing item: " + contentNode.getItem().getTitle());
				return new BrowseResult(new DIDLParser().generate(didlContent), 1, 1);
			} 
			else
			{
				if (browseFlag == BrowseFlag.METADATA) {
					didlContent.addContainer(contentNode.getContainer());
					Log.v(LOGTAG, "returning metadata of container: " + contentNode.getContainer().getTitle());

					return new BrowseResult(new DIDLParser().generate(didlContent), 1, 1);
				} 
				else 
				{
					int[] resCount = getResultContent(firstResult, maxResults, didlContent, contentNode);

					return new BrowseResult(new DIDLParser().generate(didlContent), resCount[0], resCount[1]);
				}
			}

		} catch (Exception ex) {
			throw new ContentDirectoryException(ContentDirectoryErrorCode.CANNOT_PROCESS, ex.toString());
		}
	}

	private int[] getResultContent(long firstResult, long maxResults, final DIDLContent didlContent, ContentNode contentNode) {
		int[] res = new int[2];

		Container containers = contentNode.getContainer();
		int totalMatches = containers.getChildCount();

		int toIndex;
		if (maxResults == 0)
			toIndex = totalMatches;
		else
			toIndex = (firstResult + maxResults) < totalMatches ? (int) (firstResult + maxResults) : totalMatches;

		List<Item> itemList = containers.getItems();
		int itemSize = itemList.size();
		
		List<Container> containerList = containers.getContainers();
		
		if (toIndex <= itemSize) {
			for (Item item : itemList.subList((int) firstResult, toIndex)) {
				didlContent.addItem(item);
				res[0]++;
			}
		} else if (firstResult >= itemSize) {
			for (Container container : containerList.subList((int) firstResult, toIndex)) {
				didlContent.addContainer(container);
				res[0]++;
			}
		} else {
			for (Item item : itemList.subList((int) firstResult, itemSize)) {
				didlContent.addItem(item);
				res[0]++;
			}
			
			for (Container container : containerList.subList(0, (int) (maxResults - (itemSize - firstResult)))) {
				didlContent.addContainer(container);
				res[0]++;
			}
		}

		res[1] = totalMatches;

		return res;
	}

	@Override
	public BrowseResult search(String containerId, String searchCriteria,
			String filter, long firstResult, long maxResults,
			SortCriterion[] orderBy) throws ContentDirectoryException {
		// You can override this method to implement searching!
		return super.search(containerId, searchCriteria, filter, firstResult, maxResults, orderBy);
	}
}
