package com.hisilicon.dlna.dmc.processor.interfaces;

import java.util.List;
import java.util.Map;

import org.teleal.cling.support.model.DIDLObject;

public interface DMSProcessor {
	void browse(String objectID, int startIndex, int maxResult, DMSProcessorListner listener);

	boolean back(List<String> traceID, int maxResult, DMSProcessorListner listener);

	void dispose();

	public interface DMSProcessorListner {
		void onBrowseComplete(String objectID, boolean haveNext, Map<String, List<? extends DIDLObject>> result);

		void onBrowseFail(String message);
	}
}
