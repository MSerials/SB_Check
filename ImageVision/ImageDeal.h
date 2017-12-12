#pragma once
#include "stdafx.h"
#include "halcon.h"

// CImageDeal 命令目标
#ifndef __DEAL_IMAGE___
#define  __DEAL_IMAGE___


#include <vector>
using namespace std;

class CImageDeal : public CObject
{
public:
	CImageDeal();
	virtual ~CImageDeal();
public:
	
	bool Back_Train(const std::vector<std::string>& imgpath, const HTuple& WinHandle, const _Params &params);// { return true; };
	bool Front_Train(const std::vector<std::string>& imgpath, const HTuple& WinHandle, const _Params &params);
	int Front_Deal(const Hobject src, const HTuple& WinHandle, const _Params &params);//image roi,result
	int Back_Deal(const Hobject src, const HTuple& WinHandle, const _Params &params);// { return 0; }//image roi,result

	Halcon::HTuple CheckHole(const Hobject src, const HTuple& WinHandle, const _Params &params); //return result
	//添加相机一排除框
	bool unionTNoROI(const Halcon::Hobject &hobj){ set_check("~give_error"); Halcon::union2(TopNoDetect, hobj, &TopNoDetect); set_check("~give_error"); return true; }
	bool unionBNoROI(const Halcon::Hobject &hobj){ set_check("~give_error"); Halcon::union2(BottomNoDetect, hobj, &BottomNoDetect); set_check("~give_error"); return true; }
	
	Halcon::Hobject & GetTNoROI(){ return TopNoDetect; }
	void clearTNROI(){ set_check("~give_error"); Halcon::Hobject obj,co; Halcon::complement(TopNoDetect, &obj); Halcon::union2(obj, TopNoDetect, &co); Halcon::complement(co, &TopNoDetect);set_check("give_error"); }
	Halcon::Hobject & GetBNoROI(){ return BottomNoDetect; }
	void clearBNROI(){ set_check("~give_error"); Halcon::Hobject obj,co; Halcon::complement(BottomNoDetect, &obj); Halcon::union2(obj, BottomNoDetect, &co); Halcon::complement(co, &BottomNoDetect); set_check("give_error"); }
	

	//Halcon::find_shape_model(TopImage, TopShapeModelID, HTuple(-10).Rad(), HTuple(20).Rad(), 0.5,
	bool write_top_variation_model(CString prj){ return (H_MSG_TRUE == Halcon::write_variation_model(TopVariationModelID, (char*)(LPCSTR)(CStringA)(prj + L"/TopVar.dat"))); }
	bool write_top_shape(CString prj){ return (H_MSG_TRUE == Halcon::write_shape_model(TopShapeModelID, (char*)(LPCSTR)(CStringA)(prj+L"/TopShape.shm"))); }
	bool write_top_roi(CString prj){ return  (H_MSG_TRUE == Halcon::write_region(TopRegionROI, (char*)(LPCSTR)(CStringA)(prj + L"/TopROI.reg"))); }
	bool write_top_nroi(CString prj){ return (H_MSG_TRUE == Halcon::write_region(TopNoDetect, (char*)(LPCSTR)(CStringA)(prj + L"/TopNROI.reg"))); }
	bool write_top_rowref(CString prj){ return  (H_MSG_TRUE == Halcon::write_tuple(TopRowRef, (char*)(LPCSTR)(CStringA)(prj + L"/TopRRef"))); }
	bool write_top_colref(CString prj){ return  (H_MSG_TRUE == Halcon::write_tuple(TopColumnRef, (char*)(LPCSTR)(CStringA)(prj + L"/TopCRef"))); }

	bool read_top_variation_model(CString prj){ return (H_MSG_TRUE == Halcon::read_variation_model((char*)(LPCSTR)(CStringA)(prj + L"/TopVar.dat"), &TopVariationModelID)); }
	bool read_top_shape(CString prj){ return (H_MSG_TRUE == Halcon::read_shape_model((char*)(LPCSTR)(CStringA)(prj + L"/TopShape.shm"), &TopShapeModelID)); }
	bool read_top_roi(CString prj){ set_system("clip_region", "false"); return  (H_MSG_TRUE == Halcon::read_region(&TopRegionROI, (char*)(LPCSTR)(CStringA)(prj + L"/TopROI.reg"))); }
	bool read_top_nroi(CString prj){ set_system("clip_region", "false"); return (H_MSG_TRUE == Halcon::read_region(&TopNoDetect, (char*)(LPCSTR)(CStringA)(prj + L"/TopNROI.reg"))); }
	bool read_top_rowref(CString prj){ return (H_MSG_TRUE == Halcon::read_tuple((char*)(LPCSTR)(CStringA)(prj + L"/TopRRef"), &TopRowRef)); }
	bool read_top_colref(CString prj){ return (H_MSG_TRUE == Halcon::read_tuple((char*)(LPCSTR)(CStringA)(prj + L"/TopCRef"), &TopColumnRef)); }
	
	bool write_bottom_variation_model(CString prj){  return (H_MSG_TRUE == Halcon::write_variation_model(BottomVariationModelID, (char*)(LPCSTR)(CStringA)(prj + L"/BottomVar.dat"))); }
	bool write_bottom_shape(CString prj){ return (H_MSG_TRUE == Halcon::write_shape_model(BottomShapeModelID, (char*)(LPCSTR)(CStringA)(prj + L"/BottomShape.shm"))); }
	bool write_bottom_roi(CString prj){ return  (H_MSG_TRUE == Halcon::write_region(BottomRegionROI, (char*)(LPCSTR)(CStringA)(prj + L"/BottomROI.reg"))); }
	bool write_bottom_nroi(CString prj){ return (H_MSG_TRUE == Halcon::write_region(BottomNoDetect, (char*)(LPCSTR)(CStringA)(prj + L"/BottomNROI.reg"))); }
	bool write_bottom_rowref(CString prj){ return  (H_MSG_TRUE == Halcon::write_tuple(BottomRowRef, (char*)(LPCSTR)(CStringA)(prj + L"/BottomRRef"))); }
	bool write_bottom_colref(CString prj){ return  (H_MSG_TRUE == Halcon::write_tuple(BottomColumnRef, (char*)(LPCSTR)(CStringA)(prj + L"/BottomCRef"))); }
	
	bool read_bottom_variation_model(CString prj){ return (H_MSG_TRUE == Halcon::read_variation_model((char*)(LPCSTR)(CStringA)(prj + L"/BottomVar.dat"), &BottomVariationModelID)); }
	bool read_bottom_shape(CString prj){ return (H_MSG_TRUE == Halcon::read_shape_model((char*)(LPCSTR)(CStringA)(prj + L"/BottomShape.shm"), &BottomShapeModelID)); }
	bool read_bottom_roi(CString prj){ set_system("clip_region", "false"); return  (H_MSG_TRUE == Halcon::read_region(&BottomRegionROI, (char*)(LPCSTR)(CStringA)(prj + L"/BottomROI.reg"))); }
	bool read_bottom_nroi(CString prj){ set_system("clip_region", "false"); return (H_MSG_TRUE == Halcon::read_region(&BottomNoDetect, (char*)(LPCSTR)(CStringA)(prj + L"/BOttomNROI.reg"))); }
	bool read_bottom_rowref(CString prj){ return (H_MSG_TRUE == Halcon::read_tuple((char*)(LPCSTR)(CStringA)(prj + L"/BottomRRef"), &BottomRowRef)); }
	bool read_bottom_colref(CString prj){ return (H_MSG_TRUE == Halcon::read_tuple((char*)(LPCSTR)(CStringA)(prj + L"/BottomCRef"), &BottomColumnRef)); }

	bool write_params(CString prj){
		if (write_top_params(prj)
			&& write_bottom_params(prj))
			return true;
		return false;
	}

	bool read_params(CString prj){
		if (read_top_params(prj)
			&& read_bottom_params(prj)
			)
			return true;
		return false;
	}

	bool read_top_params(CString prj)
	{
		set_check("~give_error");
		if (read_top_variation_model(prj)
			&& read_top_shape(prj)
			&& read_top_roi(prj)
			&& read_top_rowref(prj)
			&& read_top_colref(prj)
			&& read_top_nroi(prj)
			)
			return true;
		return false;
	}	
	

	bool read_bottom_params(CString prj)
	{
		set_check("~give_error");
		if ( read_bottom_variation_model(prj)
			&& read_bottom_shape(prj)
			&& read_bottom_roi(prj)
			&& read_bottom_rowref(prj)
			&& read_bottom_colref(prj)
			&& read_bottom_nroi(prj)
			)
			return true;
		return false;
	}

	bool write_top_params(CString prj)
	{
		set_check("~give_error");
		if (write_top_variation_model(prj)
			&& write_top_shape(prj)
			&& write_top_roi(prj)
			&& write_top_colref(prj)
			&& write_top_rowref(prj)
			&& write_top_nroi(prj)
			)
			return true;
		return false;
	}

	bool write_bottom_params(CString prj)
	{
		set_check("~give_error");
		if(write_bottom_variation_model(prj)
			&& write_bottom_shape(prj)
			&& write_bottom_roi(prj)
			&& write_bottom_rowref(prj)
			&& write_bottom_colref(prj)
			&& write_bottom_nroi(prj)
			)
			return true;
		return false;
	}


private:
	void Dis_Obj(const Hobject& hobject, const HTuple& WinHandle);
//public:
	Hobject  TopoImage, TopbImage, TopROI_0, TopImage, TopRegion;
	Hobject  TopRegionFillUp, TopRegionDifference, TopRegionTrans, TopRegionDilation;
	Hobject  TopImageReduced, TopModelImages, TopModelRegions, TopModel;
	Hobject  TopImageTrans, TopMeanImage, TopVarImage, TopRegionROI, TopRegionDiff;
	Hobject  TopConnectedRegions, TopRegionsError, TopNoDetect;


	Hobject  BottomoImage, BottombImage, BottomROI_0, BottomImage, BottomRegion;
	Hobject  BottomRegionFillUp, BottomRegionDifference, BottomRegionTrans, BottomRegionDilation;
	Hobject  BottomImageReduced, BottomModelImages, BottomModelRegions, BottomModel;
	Hobject  BottomImageTrans, BottomMeanImage, BottomVarImage, BottomRegionROI, BottomRegionDiff;
	Hobject  BottomConnectedRegions, BottomRegionsError, BottomNoDetect;

	// Local control variables 
	HTuple  Topnumofmodel, Topimagepath, Topirow, Topicol, Topiwidth;
	HTuple  Topiheight, TopWidth, TopHeight, TopWindowHandle, TopOS, TopArea;
	HTuple  TopRowRef, TopColumnRef, TopShapeModelID, TopVariationModelID;
	HTuple  TopI, TopRow, TopColumn, TopAngle, TopScore, TopHomMat2D, Topdetectpath;
	HTuple  Topnumdetect, TopNumError;

	HTuple  Bottomnumofmodel, Bottomimagepath, Bottomirow, Bottomicol, Bottomiwidth;
	HTuple  Bottomiheight, BottomWidth, BottomHeight, BottomWindowHandle, BottomOS, BottomArea;
	HTuple  BottomRowRef, BottomColumnRef, BottomShapeModelID, BottomVariationModelID;
	HTuple  BottomI, BottomRow, BottomColumn, BottomAngle, BottomScore, BottomHomMat2D, Bottomdetectpath;
	HTuple  Bottomnumdetect, BottomNumError;
};


#endif