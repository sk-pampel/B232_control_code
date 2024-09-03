#pragma once
#include "ConfigurationSystems/profileSettings.h"
#include "expSystemRunList.h"
#include <string>

struct autoCalConfigInfo { 
	profileSettings prof; 
	std::string fileName;
	std::string infoStr;  
}; 

const std::vector<autoCalConfigInfo> AUTO_CAL_LIST {
	{
		/*prof*/ {"Atom_Loading_And_Imaging_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "BASIC_SINGLE_ATOMS",
		/*infostr*/ "Running Basic Single Atom Loading and Imaging Test...\r\n"
	},
	{
		/*prof*/ {"release_recapture_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "SINGLE_ATOM_TEMP",
		/*infostr*/ "Running Release and Recapture...\r\n"
	},
	{
		/*prof*/ {"pushout_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "PUSHOUT_TEST",
		/*infostr*/ "Running Pushout...\r\n"
	},
	{
		/*prof*/ {"thermal_top_sideband_Raman_spectroscopy_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "THERMAL_TOP_SIDEBAND_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running Thermal Top Raman Sideband Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "3DGSBC_Carrier_Calibration_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_TOP_CARRIER_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running 3DSBC Top Carrier Raman Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "3DGSBC_Top_Sideband_Spectroscopy_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_TOP_SIDEBAND_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running 3DSBC Top Raman Sideband Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "3DGSBC_Top_BSB_PiTime_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_TOP_BSB_RABI",
		/*infostr*/ "Running 3DSBC Top BSB Pi Time...\r\n"
	},
	{
		/*prof*/ { "3DGSBC_Axial_Sideband_Spectroscopy_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_AXIAL_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running 3DSBC Axial Raman Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "thermal_Axial_Sideband_Spectroscopy_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "THERMAL_AXIAL_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running Thermal Axial Raman Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "3DGSBC_Axial_BSB_PiTime_1x1", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_AXIAL_BSB_RABI",
		/*infostr*/ "Running 3DSBC Axial BSB Pi Time...\r\n"
	},
	{
		/*prof*/ {"Automated-MOT-Temperature-Measurement", "MOT", MOT_ROUTINES_ADDRESS},
		/*filename*/ "MOT_TEMPERATURE",
		/*infostr*/ "Running Mot Temperature Calibration...\r\n"
	},
	{
		/*prof*/ {"Automated-PGC-Temperature-Measurement", "PGC", PGC_ROUTINES_ADDRESS},
		/*filename*/ "RED_PGC_TEMPERATURE",
		/*infostr*/ "Running PGC Temperature Calibration...\r\n"
	}
	//{
	//	/*prof*/ { "Mot_Size_Measurement", "MOT", MOT_ROUTINES_ADDRESS },
	//	/*filename*/ "MOT_NUMBER",
	//	/*infostr*/ "Running Mot Fill Calibration...\r\n"
	//},
	//{
	//	/*prof*/ {"Automated-Grey-PGC-Temperature-Measurement", "PGC", PGC_ROUTINES_ADDRESS},
	//	/*filename*/ "GREY_MOLASSES_TEMPERATURE",
	//	/*infostr*/ "Running Grey Molasses Temperature Calibration...\r\n"
	//},

	//{
	//	/*prof*/ { "Depth_Measurement_Deep", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
	//	/*filename*/ "DEPTH_MEASUREMENT_DEEP",
	//	/*infostr*/ "Running Deep Depth Measurement...\r\n"
	//},
	//{
	//	/*prof*/ { "Depth_Measurement_Shallow", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
	//	/*filename*/ "DEPTH_MEASUREMENT_SHALLOW",
	//	/*infostr*/ "Running Shallow Depth Measurement...\r\n"
	//},
	//{		
	//	/*prof*/ { "Lifetime_Measurement", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
	//	/*filename*/ "LIFETIME_MEASUREMENT",
	//	/*infostr*/ "Running Lifetime Measurement...\r\n"
	//},
	//{
	//	/*prof*/ { "StandardTunneling", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
	//	/*filename*/ "StandardTunneling",
	//	/*infostr*/ "Running Tunneling bias scan...\r\n"
	//}
};
