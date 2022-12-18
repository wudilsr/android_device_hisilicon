package com.hisilicon.dlna.dmc.processor.impl;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.teleal.cling.controlpoint.ControlPoint;
import org.teleal.cling.model.action.ActionInvocation;
import org.teleal.cling.model.message.UpnpResponse;
import org.teleal.cling.model.meta.Device;
import org.teleal.cling.model.meta.Service;
import org.teleal.cling.model.types.ServiceType;
import org.teleal.cling.support.contentdirectory.callback.Browse;
import org.teleal.cling.support.model.BrowseFlag;
import org.teleal.cling.support.model.DIDLContent;
import org.teleal.cling.support.model.DIDLObject;
import org.teleal.cling.support.model.SortCriterion;
import org.teleal.cling.support.model.container.Container;
import org.teleal.cling.support.model.item.Item;

import com.hisilicon.dlna.dmc.processor.interfaces.DMSProcessor;

public class DMSProcessorImpl implements DMSProcessor
{
	@SuppressWarnings("rawtypes")
	private Device m_device;
	
	private ControlPoint m_controlPoint;

	@SuppressWarnings("rawtypes")
	public DMSProcessorImpl(Device device, ControlPoint controlPoint)
	{
		m_device = device;
		m_controlPoint = controlPoint;
	}

	public void dispose()
	{

	}

	/**
	 * 浏览媒体文件
	 * @param objectID 媒体ID
	 * @param startIndex  起始位置
	 * @param maxResult 本次浏览最大量
	 * @param listener 回调
	 */
	@Override
	public void browse(String objectID, int startIndex, int maxResult, final DMSProcessorListner listener)
	{
		executeBrowse(objectID, startIndex, maxResult, listener);
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	private void executeBrowse(final String objectID, final int startIndex, final int defaultMaxResult, final DMSProcessorListner listener)
	{
		Service contentDirectoryService = m_device.findService(new ServiceType("schemas-upnp-org", "ContentDirectory"));
		
		if ( contentDirectoryService != null )
		{
			int maxResults = defaultMaxResult + 1;
			
			Browse browse = new Browse(contentDirectoryService, objectID, BrowseFlag.DIRECT_CHILDREN, Browse.CAPS_WILDCARD, startIndex, (long) maxResults, new SortCriterion[] { new SortCriterion(true, "dc:title") })
			{
				@Override
				public void received(ActionInvocation actionInvocation, DIDLContent didlContent)
				{
					try
					{
						Map<String, List<? extends DIDLObject>> result = new HashMap<String, List<? extends DIDLObject>>();
						
						List<Container> containers = didlContent.getContainers();
						List<Item> items = didlContent.getItems();
						
						boolean haveNext = false;
						
						if (containers.size() > defaultMaxResult)
						{
							haveNext = true;
							containers.remove(containers.size() - 1);
						}
						else if (items.size() > defaultMaxResult || items.size() + containers.size() > defaultMaxResult)
						{
							haveNext = true;
							items.remove(items.size() - 1);
						}
						
						result.put("Containers", containers);
						result.put("Items", items);
						
						listener.onBrowseComplete(objectID, haveNext, result);
					}
					catch (Exception e)
					{
						e.printStackTrace();
						listener.onBrowseFail(e.getMessage());
					}
				}

				@Override
				public void updateStatus(Status status)
				{
					
				}

				@Override
				public void failure(ActionInvocation invocation, UpnpResponse operation, String defaultMsg)
				{
					listener.onBrowseFail(defaultMsg);
				}
				
			};
			
			m_controlPoint.execute(browse);
		}
		else
		{
			listener.onBrowseFail("");
		}
	}

	@Override
	public boolean back(List<String> m_traceID, int maxResult, DMSProcessorListner listener)
	{
		int traceSize = m_traceID.size();
		if (traceSize > 2)
		{
			String parentID = m_traceID.get(traceSize - 2);

			m_traceID.remove(m_traceID.size() - 1);

			browse(parentID, 0, maxResult, listener);

			return true;
		}

		return false;
	}
}
