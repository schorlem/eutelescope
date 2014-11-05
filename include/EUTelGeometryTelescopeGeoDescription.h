/* 
 * File:   EUTelGeometryTelescopeGeoDescription.h
 *
 */

#ifndef EUTELGEOMETRYTELESCOPEGEODESCRIPTION_H
#define	EUTELGEOMETRYTELESCOPEGEODESCRIPTION_H

// C++
#include <map>
#include <string>

// LCIO includes
#include "LCIOSTLTypes.h"

// MARLIN
#include "marlin/Global.h"

// GEAR includes
#include "gear/GearMgr.h"
#include "gearimpl/SiPlanesLayerLayoutImpl.h"
#include "gearimpl/SiPlanesParametersImpl.h"

#include "gearimpl/TrackerPlanesLayerLayoutImpl.h"
#include "gearimpl/TrackerPlanesParametersImpl.h"

#include "gear/BField.h"

// EUTELESCOPE
#include "EUTelUtility.h"
#include "EUTelGenericPixGeoMgr.h"

// ROOT
#if defined(USE_ROOT) || defined(MARLIN_USE_ROOT)
#include "TMatrixD.h"
#else
#error *** You need ROOT to compile this code.  *** 
#endif

//Eigen
#include <Eigen/Core>
// ROOT
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TVector3.h"

// built only if GEAR is available
#ifdef USE_GEAR

/** @class EUTelGeometryTelescopeGeoDescription
 * This class is supposed to keep globally accesible 
 * telescope geometry description.
 * 
 * It is based on singleton design pattern and furnishes
 * a facade for GEAR description
 */

namespace eutelescope {

    namespace geo{

	struct EUTelPlane
	{
		/**Spatial location*/
		double xPos, yPos, zPos;
		/**Spatial location errors/uncertainties*/
		//double xPosErr, yPosErr, zPosErr;
		/**Euler rotations*/
		double alpha, beta, gamma;
		/**Euler uncertainties*/
		//double alphaErr, betaErr, gammaErr;
		/**Pixel geometry name*/
		std::string pixGeoName;
		/**2D flip entries*/
		double r1, r2, r3, r4;
		/**Size of plane*/
		double xSize, ySize, zSize;
		/**Pixel counts*/
		int xPixelNo, yPixelNo;
		/**Pixel pitch*/
		double xPitch, yPitch;
		/**Radiation length TODO: UNIT*/
		double radLength;
		/**Resolution of sensor*/
		double xRes, yRes;
	};

        // Iterate over registered GEAR objects and construct their TGeo representation
        const Double_t PI     = 3.141592653589793;
        const Double_t DEG    = 180./PI; 
        const Double_t RADIAN = PI/180.; 

        class EUTelGeometryTelescopeGeoDescription {
            
        private:
            /** */
            EUTelGeometryTelescopeGeoDescription();

            /** */ 
            DISALLOW_COPY_AND_ASSIGN(EUTelGeometryTelescopeGeoDescription)      // prevent users from making (default) copies of processors

            /** need only for pede2lcio*/
            gear::GearMgr* _gearManager;

            /** */ 
            bool _siPlanesDefined;

            /** */ 
            bool _telPlanesDefined;

        public:
            /** Retrieves the instanstance of geometry.
             * Performs lazy intialization if necessary.
             * @TODO this routine has to be considered to be constant
             */
            static EUTelGeometryTelescopeGeoDescription& getInstance( gear::GearMgr* _g );
  
            /** */
            void updateGearManager();  
 
            /** */
            unsigned counter() { return _counter++; }

            /** needed only for pede2lcio*/ 
            void setGearManager( gear::GearMgr* value ) { _gearManager = value ; }

            /** Number of planes in the setup */
            inline size_t getSiPlanesLayoutID() const { return _siPlanesLayoutID; } ;

             /** Number of planes in the setup */
            void setSiPlanesLayoutID(size_t value) { _siPlanesLayoutID = value; } ;          
                    
            /** Number of planes in the setup */
            size_t nPlanes() const;
            
            /** Z coordinates of centers of planes */
            const EVENT::DoubleVec& siPlanesZPositions() const;
           
            /** set methods */

            /** set X position  */
            void setPlaneXPosition(int sensorID, double value){ _planeSetup[sensorID].xPos = value; };
 
            /** set Y position  */
            void setPlaneYPosition(int sensorID, double value){ _planeSetup[sensorID].yPos = value; };
 
            /** set Z position  */
            void setPlaneZPosition(int sensorID, double value){ _planeSetup[sensorID].zPos = value; };
 
            /** set X rotation  */
            void setPlaneXRotation(int sensorID, double value){ _planeSetup[sensorID].alpha = value; };
 
            /** set Y rotation  */
            void setPlaneYRotation(int sensorID, double value){ _planeSetup[sensorID].beta = value; };
 
            /** set Z rotation  */
            void setPlaneZRotation(int sensorID, double value){ _planeSetup[sensorID].gamma = value; };
 
            /** set X rotation  */
            void setPlaneXRotationRadians(int sensorID, double value /* in Radians */){ _planeSetup[sensorID].alpha = value*DEG; };
 
            /** set Y rotation  */
            void setPlaneYRotationRadians(int sensorID, double value /* in Radians */){ _planeSetup[sensorID].beta = value*DEG; };
 
            /** set Z rotation  */
            void setPlaneZRotationRadians(int sensorID, double value /* in Radians */){ _planeSetup[sensorID].gamma = value*DEG; };
//GETTER
            /** */ 
            float siPlaneRotation1(int sensorID){ return _planeSetup.at(sensorID).r1; };

            /** */ 
            float siPlaneRotation2(int sensorID){ return _planeSetup.at(sensorID).r2; };

            /** */ 
            float siPlaneRotation3(int sensorID){ return _planeSetup.at(sensorID).r3; };

            /** */ 
            float siPlaneRotation4(int sensorID){ return _planeSetup.at(sensorID).r4; };
 
            /** X coordinate of center of sensor 
             * with given ID in global coordinate frame */
            double siPlaneXPosition(int sensorID){ return _planeSetup.at(sensorID).xPos; };
            
            /** Y coordinate of center of sensor 
             * with given ID in global coordinate frame */
            double siPlaneYPosition(int sensorID){ return _planeSetup.at(sensorID).yPos; };
            
            /** Z coordinate of center of sensor 
             * with given ID in global coordinate frame */
            double siPlaneZPosition(int sensorID){ return _planeSetup.at(sensorID).zPos; };
            
            /** Rotation around X axis of the global coordinate frame */
            double siPlaneXRotation(int sensorID){ return _planeSetup.at(sensorID).alpha; };
            
            /** Rotation around Y axis of global coordinate frame */
            double siPlaneYRotation(int sensorID){ return _planeSetup.at(sensorID).beta; };
            
            /** Rotation around Z axis of global coordinate frame */
            double siPlaneZRotation(int sensorID){ return _planeSetup.at(sensorID).gamma; };

             /** Rotation around X axis of the global coordinate frame */
            double siPlaneXRotationRadians(int sensorID){ return _planeSetup.at(sensorID).alpha*RADIAN; };
            
            /** Rotation around Y axis of global coordinate frame */
            double siPlaneYRotationRadians(int sensorID){ return _planeSetup.at(sensorID).beta*RADIAN; };
            
            /** Rotation around Z axis of global coordinate frame */
            double siPlaneZRotationRadians(int sensorID){ return _planeSetup.at(sensorID).gamma*RADIAN; };

            /** Sensor X side size */
            double siPlaneXSize(int sensorID){ return _planeSetup.at(sensorID).xSize; };
            
            /** Sensor Y side size */
            double siPlaneYSize(int sensorID){ return _planeSetup.at(sensorID).ySize; };
            
            /** Sensor Z side size */
            double siPlaneZSize(int sensorID){ return _planeSetup.at(sensorID).zSize; };
 
            /** Sensor X side pixel pitch [mm] */
            double siPlaneXPitch(int sensorID){ return _planeSetup.at(sensorID).xPitch; };
            
            /** Sensor Y side pixel pitch [mm] */
            double siPlaneYPitch(int sensorID){ return _planeSetup.at(sensorID).yPitch; };

            /** Sensor X side size in pixels */
            double siPlaneXNpixels(int sensorID){ return _planeSetup.at(sensorID).xPixelNo; };
            
            /** Sensor Y side size in pixels */
            double siPlaneYNpixels(int sensorID){ return _planeSetup.at(sensorID).yPixelNo; };
 
            /** Sensor X side size in pixels */
            double siPlaneXResolution(int sensorID){ return _planeSetup.at(sensorID).xRes; };
            
            /** Sensor Y side size in pixels */
            double siPlaneYResolution(int sensorID){ return _planeSetup.at(sensorID).yRes; };
            
            /** Sensor medium radiation length */
            double siPlaneRadLength(int sensorID){ return _planeSetup.at(sensorID).radLength; };
            
	    /** Name of pixel geometry library */
	    std::string geoLibName(int sensorID){ return _planeSetup.at(sensorID).pixGeoName; };
            
	    /** Plane normal vector (nx,ny,nz) */
            TVector3 siPlaneNormal(int sensorID);
            
            /** Map from sensor ID to number along Z */
            const std::map<int, int>& sensorZOrdertoIDs() const;
            
            /** Map from sensor ID to number along Z */
            const std::map<int, int>& sensorIDstoZOrder() const;
            
            int sensorIDtoZOrder( int ) const;
            
            int sensorZOrderToID( int ) const;
            
            /** Vector of all sensor IDs */
            const EVENT::IntVec& sensorIDsVec() const;

	    Eigen::Vector3d getRotationAnglesFromMatrix( Eigen::Matrix3d rotMat );
	    Eigen::Matrix3d rotationMatrixFromAngles(long double alpha, long double beta, long double gamma);
	    Eigen::Matrix3d rotationMatrixFromAngles(int sensorID);
	    void writeGEARFile(std::string filename);
        
	public:
            virtual ~EUTelGeometryTelescopeGeoDescription();

        private:
            /** reading initial info from gear: part of contructor */
	    void readSiPlanesLayout();

            /** reading initial info from gear: part of contructor */
	    void updateSiPlanesLayout();


            /** reading initial info from gear: part of contructor
              * new GEAR from branch/TelPlanes
              */
	    void readTrackerPlanesLayout(); 
           
            /**  */
	    void updateTrackerPlanesLayout(); 


            /** housing for the above two */    
            void readGear();

            void translateSiPlane2TGeo(TGeoVolume*,int );

        public:
            // TGeo stuff

            /** Initialize TGeo geometry 
             * Establish access to TGeoManager, load geometry description file.
             * 
             * @param tgeofilename name of a .root or .gdml file with valid geometry
             * 
             * @see ROOT TGeoManager::Import
             */
            void initializeTGeoDescription(std::string tgeofilename);
            
            void initializeTGeoDescription( std::string& geomName, bool dumpRoot );

            // Geometry operations
        public:
            	float findRadLengthIntegral( const double[], const double[], bool );
            
            	int getSensorID( const float globalPos[] ) const;
           
            	void local2Master( int, const double[], double[] );

		void local2masterHit(EVENT::TrackerHit* hit_input, IMPL::TrackerHitImpl* hit_output, LCCollection * hitCollectionOutput);
		
		void master2localHit(EVENT::TrackerHit* hit_input, IMPL::TrackerHitImpl* hit_output, LCCollection * hitCollectionOutput);
            
            	void master2Local( const double[], double[] );

            	void master2Localtwo(int, const double[], double[] );

		void local2MasterVec( int, const double[], double[] );
 
		void master2LocalVec( int, const double[], double[] );

		int findIntersectionWithCertainID( float x0, float y0, float z0, float px, float py, float pz, float _beamQ, int nextPlaneID, float* output);

		TVector3 getXYZfromArcLength( float x0, float y0, float z0, float px, float py, float pz, float _beamQ, float s) const;

		TMatrix getPropagationJacobianF( float x0, float y0, float z0, float px, float py, float pz, float _beamQ, float dz );

                void CalculateProjMatrix( TMatrixD& proL2m, double* hitPointGlobal )
		{  
		// Calculate projection matrix

		const TGeoHMatrix* globalH = getHMatrix( hitPointGlobal );
		const TGeoHMatrix& globalHInv = globalH->Inverse();
		const double* rotation = globalHInv.GetRotationMatrix();

		proL2m[0][0] = rotation[0]; // x projection, xx
		proL2m[0][1] = rotation[1]; // y projection, xy
		proL2m[1][0] = rotation[3]; // x projection, yx
		proL2m[1][1] = rotation[4]; // y projection, yy

    		}


        	const TGeoHMatrix* getHMatrix( const double globalPos[] );
            
            /** Magnetic field */
            const gear::BField& getMagneticFiled() const;

			/** Returns a pointer to the EUTelGenericPixGeoDescr of given plane */
			EUTelGenericPixGeoDescr* getPixGeoDescr( int );

			/** Returns the TGeo path of given plane */
			std::string  getPlanePath( int  );

        private:
            /** Silicon planes parameters as described in GEAR
             * This structure actually contains the following:
             *  @li A reference to the telescope geoemtry and layout
             *  @li An integer number saying if the telescope is w/ or w/o DUT
             *  @li An integer number saying the number of planes in the
             *  telescope.
             *
             *  This object is provided by GEAR during the init() phase and
             *  stored here for local use.
             */
            gear::SiPlanesParameters* _siPlanesParameters;

            /** Silicon plane layer layout
             * This is the real geoemetry description. For each layer
             *  composing the telescope the relevant information are
             *  available.
             *
             *  This object is taken from the _siPlanesParameters during the
             *  init() phase and stored for local use
             */
            gear::SiPlanesLayerLayout* _siPlanesLayerLayout;

            /**
             */
            gear::TrackerPlanesParameters*  _trackerPlanesParameters;
 
            /**
             */
            gear::TrackerPlanesLayerLayout* _trackerPlanesLayerLayout;

// overwrite private to public ::
        private :

            /** */
            size_t _siPlanesLayoutID;

            /** Vector of Sensor IDs */
            EVENT::IntVec _sensorIDVec;

	    /** Z coordinate of the sensors centers in global coordinate frame [mm]*/
	    EVENT::DoubleVec _siPlaneZPosition;

            /** Sensor ID map (inverse sensorIDVec) */
            std::map< int, int > _sensorIDVecMap;

            /** Map from number along the Z axis (beam axis) to sensor ID */
            std::map<int, int> _sensorZOrderToIDMap;

            /** Map from sensor ID to number along Z */
            std::map<int, int> _sensorIDtoZOrderMap;

	    /** Number of planes including DUT */
            size_t _nPlanes;

            /** Pointer to the pixel geometry manager */
            EUTelGenericPixGeoMgr* _pixGeoMgr;

	    std::map<int, EUTelPlane> _planeSetup;
        private:
	    /** Flag if geoemtry is already initialized */
	    bool _isGeoInitialized;
         
	    /** Map containing plane path (string) and corresponding planeID */
	    std::map<int, std::string> _planePath;

        public:
            // TGeo stuff
            /** @TODO this must be coupled with GEAR
             * description. No checks of consistency between GEAR and TGeo
             * descriptions are being done, currently.
             */

            /** Geometry manager global object */
            TGeoManager* _geoManager;
            //#endif // USE_TGEO

            int findNextPlaneEntrance(  double* ,  double *, int, float*  );
            int findNextPlane(  double* lpoint,  double* ldir,  float* newpoint );

            /** */
            static unsigned _counter;

        };
        
        inline EUTelGeometryTelescopeGeoDescription& gGeometry( gear::GearMgr* _g = marlin::Global::GEAR ) {
                return EUTelGeometryTelescopeGeoDescription::getInstance( _g ); 
        }
    } // namespace geo
} // namespace eutelescope

#endif  // USE_GEAR
 
#endif	/* EUTELGEOMETRYTELESCOPEGEODESCRIPTION_H */

