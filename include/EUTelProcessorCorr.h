/*
 *   This source code is part of the Eutelescope package of Marlin.
 *   You are free to use this source files for your own development as
 *   long as it stays in a public research context. You are not
 *   allowed to use it for commercial purpose. You must put this
 *   header with author names in all development based on this file.
 *
 */
#ifndef EUTELPROCESSORCORR_H
#define EUTELPROCESSORCORR_H

// eutelescope includes ".h"
#include "EUTelUtility.h"

// marlin includes ".h"
#include "marlin/Processor.h"

// lcio includes <.h>
#include <EVENT/LCRunHeader.h>
#include <EVENT/LCEvent.h>
#include <EVENT/LCCollection.h>

//aida includes
#include <AIDA/IHistogramFactory.h>
#include <AIDA/IHistogram1D.h>
#include <AIDA/IHistogram2D.h>
#include <AIDA/ITree.h>
#include <IMPL/LCCollectionVec.h>

// system includes <>
#include <string>
#include <vector>
#include <map>

namespace eutelescope {

//Helper struct to store the histogram pointers for XX, XY, YX and YY histograms.
struct corrHistos {  
	AIDA::IHistogram2D* xx;
	AIDA::IHistogram2D* xy;
	AIDA::IHistogram2D* yx;
	AIDA::IHistogram2D* yy;
};

struct preAlignHistos {
	AIDA::IHistogram1D* x;
	AIDA::IHistogram1D* y;
};


//Helper enum to address all the permutations - the last entry is to used to keep track of enum size
enum perm { x_y, mx_y, x_my, mx_my, y_x, my_x, y_mx, my_mx, last };
	
class EUTelProcessorCorr : public marlin::Processor {
  private:
	DISALLOW_COPY_AND_ASSIGN(EUTelProcessorCorr)

  public:
	virtual Processor * newProcessor() {
		return new EUTelProcessorCorr;
	}

	EUTelProcessorCorr();

	virtual void init();
	virtual void processEvent (LCEvent * event);
	virtual void end();

	double getPeakPosition (AIDA::IHistogram1D* histogram, int nbins, double lowerEdge, double upperEdge){
                double binWidth=(upperEdge-lowerEdge)/nbins;

                double maxValue=0;
                double maxBin=0;

                for ( int i=0; i<nbins; i++){
                        if (histogram->binHeight(i)>maxValue){
                                maxValue = histogram->binHeight(i);
                                maxBin = i;
                        }
                }

                double peakPos = maxBin*binWidth+lowerEdge;
                return peakPos;
	}

  private:
	std::vector<int> _sensorIDVec;
	std::map<int, std::vector<float>> _cuts;
	std::map<int, std::array<corrHistos, perm::last>> _histoMap;
	std::map<int, std::array<preAlignHistos, 2>> _histoMapPreAlign;
	std::string _hitCollectionNameInput;
	float _distCut;
	std::vector<float> _residualsXMin;
        std::vector<float> _residualsYMin;
        std::vector<float> _residualsXMax;
        std::vector<float> _residualsYMax;	
        std::vector<int> _maxHitCut;	
	std::string _GEARFileSuffix;
	void bookHistos();
	std::map<int, int> _sensorIDtoZOrderMap; //sensor ID to position along Z id
};

//! A global instance of the processor
EUTelProcessorCorr gEUTelProcessorCorr;

}//close eutelescope namespace scope
#endif