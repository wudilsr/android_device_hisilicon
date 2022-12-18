package com.discretix.drmactions;

import android.content.Context;
import android.drm.DrmManagerClient;
import android.util.Log;

import com.discretix.drmactions.auxillary.Utilities;
import com.discretix.drmassist.DrmActionSync;

public class DecryptSession extends DrmActionSync {

		static
		{
			System.loadLibrary("DrmAssistJNI");
		}
			/*
			 * (non-Javadoc)
			 * @see com.discretix.drmassist.DrmActionBase#getName()
			 */
			public String getName() {
				return "Decrypt session tests";
			}

			/*
			 * (non-Javadoc)
			 * @see com.discretix.drmassist.DrmActionBase#isSupported(java.lang.String, java.lang.String)
			 */
			public boolean isSupported(String extension, String filePath) {
				return Utilities.isPlayreadyDrm(extension);
			}

			/*
			 * (non-Javadoc)
			 * @see com.discretix.drmassist.DrmActionSync#perform(android.content.Context, java.lang.String, java.lang.String)
			 */
			protected String perform(Context context, String filePath, String extension) {
				DrmManagerClient drmClient = new DrmManagerClient(context);

				// run all test for current file
				String res = Decrypt(3, filePath);
				Log.d("Decrypt Session", "Decrypt session for local file returned " + res);

				return res;

			}

			private native String Decrypt(int testnum, String filename);
		}
