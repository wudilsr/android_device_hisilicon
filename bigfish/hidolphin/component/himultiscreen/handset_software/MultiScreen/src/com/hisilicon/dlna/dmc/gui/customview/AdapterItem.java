package com.hisilicon.dlna.dmc.gui.customview;

public class AdapterItem {
	protected Object m_data;

	public AdapterItem(Object data) {
		m_data = data;
	}

	public Object getData() {
		return m_data;
	}

	@Override
	public boolean equals(Object o) {
		if (o != null && o instanceof AdapterItem) {
			AdapterItem other = (AdapterItem) o;
			if (other.m_data == null)
				return m_data == null;
			else if (m_data == null)
				return false;
			else
				return other.m_data.equals(m_data);

		}
		return false;
	}
}
