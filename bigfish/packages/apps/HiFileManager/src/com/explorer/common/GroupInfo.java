package com.explorer.common;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class GroupInfo {
	private String name;// group name
	private List<Map<String, String>> childList;// Group following a collection
												// of friends

	public GroupInfo() {
		childList = new ArrayList<Map<String, String>>();
	}

	public GroupInfo(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<Map<String, String>> getChildList() {
		return childList;
	}

	public void setChildList(List<Map<String, String>> childList) {
		this.childList = childList;
	}

}
