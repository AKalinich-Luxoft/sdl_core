package com.ford.syncV4.android.activity.mobilenav;

import android.content.Context;
import android.widget.CheckBox;

import com.ford.syncV4.android.R;

/**
 * Created by Andrew Batutin on 8/30/13
 */
public class MobileNaviEncryptCheckBoxState extends CheckBoxState {

    public MobileNaviEncryptCheckBoxState(CheckBox item, Context context) {
        super(item, context);
        textStringOff = getResources().getString(R.string.secure_service_check_view_off);
        textStringOn = getResources().getString(R.string.secure_service_send_rpc);
        setStateOff();
    }
}