#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct gbdt_feature {
        double SHOP_ARRIVAL_TIME;
        double SHOP_TIMEIDX_ARRIVAL_TIME;
        double SHOP_LEAVE_TIME;
        double SHOP_TIMEIDX_LEAVE_TIME;
        double SHOP_CUSTOM_TIME;
        double SHOP_TIMEIDX_CUSTOM_TIME;
        double SHOP_AVG_ORDER;
        double SHOP_AVG_DIST;
        double SHOP_TIMEIDX_OVERSTOCK;
        double SHOP_TIMEIDX_INORDER;
        double SHOP_TIMEIDX_NET_INFLOW;
        double SHOP_DISTIDX_CUSTOM_TIME;
        double AREA_ARRIVAL_TIME;
        double AREA_TIMEIDX_ARRIVAL_TIME;
        double AREA_LEAVE_TIME;
        double AREA_TIMEIDX_LEAVE_TIME;
        double AREA_CUSTOM_TIME;
        double AREA_TIMEIDX_CUSTOM_TIME;
        double AREA_AVG_ORDER;
        double AREA_TIMEIDX_ORDER;
        double AREA_AVG_RIDER;
        double AREA_TIMEIDX_RIDER;
        double AREA_TIMEIDX_TOSHOP_ORDER;
        double AREA_TIMEIDX_LEAVESHOP_ORDER;
        double AREA_TIMEIDX_TOCUSTOM_ORDER;
        double AREA_TIMEIDX_TOSHOP_AVGLOAD;
        double AREA_TIMEIDX_LEAVESHOP_AVGLOAD;
        double AREA_TIMEIDX_TOCUSTOM_AVGLOAD;
        double AREA_AVG_DIST;
        double AREA_DISTIDX_ARRIVAL_TIME;
        double AREA_DISTIDX_TIMEIDX_ARRIVAL_TIME;
        double AREA_DISTIDX_LEAVE_TIME;
        double AREA_DISTIDX_TIMEIDX_LEAVE_TIME;
        double AREA_DISTIDX_CUSTOM_TIME;
        double AREA_DISTIDX_TIMEIDX_CUSTOM_TIME;
        double SHOP_REALTIME_ARRIVAL_TIME;
        double SHOP_REALTIME_LEAVE_TIME;
        double SHOP_REALTIME_CUSTOM_TIME;
        double SHOP_REALTIME_ORDER;
        double SHOP_REALTIME_AVG_DIST;
        double SHOP_REALTIME_OVERSTOCK;
        double SHOP_REALTIME_NET_INFLOW;
        double AREA_REALTIME_ARRIVAL_TIME;
        double AREA_REALTIME_LEAVE_TIME;
        double AREA_REALTIME_CUSTOM_TIME;
        double AREA_REALTIME_ORDER;
        double AREA_REALTIME_RIDER;
        double AREA_REALTIME_TOSHOP_ORDER;
        double AREA_REALTIME_LEAVESHOP_ORDER;
        double AREA_REALTIME_TOCUSTOM_ORDER;
        double AREA_REALTIME_TOSHOP_AVGLOAD;
        double AREA_REALTIME_LEAVESHOP_AVGLOAD;
        double AREA_REALTIME_TOCUSTOM_AVGLOAD;
        double AREA_REALTIME_AVG_DIST;
        double AREA_REALTIME_DISTIDX_ARRIVAL_TIME;
        double AREA_REALTIME_DISTIDX_LEAVE_TIME;
        double AREA_REALTIME_DISTIDX_CUSTOM_TIME;
        double ORDER_DIST;
        double ORDER_WEEKDAY;
        double ORDER_IS_WEEKEND;
        double ORDER_TIMEIDX;
};

double gbdt_scoring(struct gbdt_feature feas);

#ifdef __cplusplus    
}
#endif
