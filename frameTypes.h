typedef short B16;
typedef char B8;

//站点通信成功率信息结构
typedef struct success_rate_info
{
	B16 station_TEI : 12;		//站点的TEI
	B16 saved : 4;				//保留
	B16 d_success_rate : 8;			//下行通信成功率
	B16 u_success_rate : 8;			//上行通信成功率
};
//通信成功率上报报文
typedef struct msg_success_rate
{
	B16 TEI : 12;				//站点TEI
	B16 saved : 4;				//保留
	B16 station_count[2];		//站点总数
	/*
	B16 station_TEI : 12;		//站点的TEI
	B16 saved_1 : 4;			//保留
	B8 d_success_rate;			//下行通信成功率
	B8 u_success_rate;			//上行通信成功率
	*/
	struct success_rate_info rate_info[0];//通信成功率信息,长度可变
};

//邻居网络信息结构
typedef struct neighborNet
{
	B8 item[3];
};
//网络冲突上报报文
typedef struct msg_clash_report
{
	B16 mac_CCO[3];				//CCO MAC地址
	B8 neighborNet_count;		//邻居网络个数
	B8 netId_bLength;			//网络号字节宽度
	struct neighborNet net_info[0];//邻居网络信息，长度可变
};

//过零NTB采集指示报文
typedef struct msg_NTB_collect
{
	B16 TEI : 12;				//站点TEI
	B16 saved : 4;				//保留
	B8 collect_station;			//采集站点
	B8 collect_time;			//采集周期
	B8 collect_nums;			//采集数量
};

//过零NTB告知报文
typedef struct msg_NTB_report
{
	B16 TEI : 12;				//站点TEI
	B16 saved : 4;				//保留
	B8 report_nums_all;			//告知总数量
	B8 report_nums_1;			//相线1差值告知数量
	B8 report_nums_2;			//相线2差值告知数量
	B8 report_nums_3;			//相线3差值告知数量
	B16 NTB_base[2];			//基准NTB
	B16 diff_info[0];			//相线1、2、3过零NTB差值，长度可变
};

//路由修复报文负载数据结构
typedef struct payload_route
{
	B16 TEI : 12;				//TEI
	B16 saved : 4;				//保留
	B8 success_rate;			//通信成功率
	B8 channel_quality;			//信道质量
};
//路由请求报文
typedef struct msg_route_request
{
	B8 version;					//版本
	B16 req_serial_num[2];		//路由请求序列号
	B8 saved : 3;				//保留
	B8 path_prefer_sign : 1;	//路径优选标志
	B8 payload_type : 4;		//负载数据类型
	B8 payload_len;				//负载数据长度
	struct payload_route payload[0];//负载数据，长度可变
};
//路由回复报文
typedef struct msg_route_reply
{
	B8 version;					//版本
	B16 req_serial_num[2];		//路由请求序列号
	B8 saved : 4;				//保留
	B8 payload_type : 4;		//负载数据类型
	B8 payload_len;				//负载数据长度
	struct payload_route payload[0];//负载数据，长度可变
/*
#if (payload_type == "0x1")
	B16 TEI_0 : 12;				//TEIO
	B16 saved_0 : 4;			//保留
	B8 success_rate_0;			//通信成功率0
	B8 channel_quality_0;		//信道质量0
	//...
#endif
*/
};

//路由错误报文
typedef struct msg_route_error
{
	B8 version;					//版本
	B16 req_serial_num[2];		//路由请求序列号
	B8 saved;					//保留
	B8 unreach_station_nums;	//
	B16 unreach_station[0];		//不可达站点列表，长度可变
};

//路由应答报文
typedef struct msg_route_response
{
	B8 version;					//版本
	B16 req_serial_num[2];		//路由请求序列号
};

//链路确认请求报文
typedef struct msg_linkConfirm_request
{
	B8 version;					//版本
	B16 req_serial_num[2];		//路由请求序列号
	B8 saved;					//保留
	B8 definite_station_nums;	//
	B16 definite_station[0];	//确认站点列表，长度可变
};

//链路确认回应报文
typedef struct msg_linkConfirm_response
{
	B8 version;					//版本
	B16 req_serial_num[2];		//路由请求序列号
	B8 station_level;			//层级
	B8 channel_quality;			//信道质量
	B8 path_prefer_sign : 1;	//路径优选标志
	B8 saved : 7;				//保留
};