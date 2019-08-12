package com.csimum.baixiniu.ui.widget;

import android.content.Context;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.view.MotionEvent;

public class AlphaChangeTextView extends android.support.v7.widget.AppCompatTextView {
    public AlphaChangeTextView(Context context) {
        super(context);
    }

    public AlphaChangeTextView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case 0:
                this.setAlpha(0.6F);
                break;
            case 1:
            case 3:
                this.setAlpha(1.0F);
            case 2:
        }
        return super.onTouchEvent(event);
    }
}
