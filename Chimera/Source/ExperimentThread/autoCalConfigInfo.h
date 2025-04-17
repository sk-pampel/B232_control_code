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
		/*prof*/ {"loading_survival", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "BASIC_SINGLE_ATOMS",
		/*infostr*/ "Running Basic Single Atom Loading and Imaging Test...\r\n"
	},
	{
		/*prof*/ {"release_recapture", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "SINGLE_ATOM_TEMP",
		/*infostr*/ "Running Release and Recapture...\r\n"
	},
	{
		/*prof*/ {"pushout", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "PUSHOUT_TEST",
		/*infostr*/ "Running Pushout...\r\n"
	},
	{
		/*prof*/ {"thermal_radial_spectroscopy", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms"},
		/*filename*/ "THERMAL_TOP_SIDEBAND_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running Thermal Top Raman Sideband Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "raman_carrier", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_TOP_CARRIER_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running 3DSBC Top Carrier Raman Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "raman_radial_spectroscopy", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_TOP_SIDEBAND_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running 3DSBC Top Raman Sideband Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "raman_axial_spectroscopy", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_AXIAL_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running 3DSBC Axial Raman Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "thermal_axial_spectroscopy", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "THERMAL_AXIAL_RAMAN_SPECTROSCOPY",
		/*infostr*/ "Running Thermal Axial Raman Spectroscopy...\r\n"
	},
	{
		/*prof*/ { "raman_axial_bsb_pi_pulse", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_AXIAL_BSB_RABI",
		/*infostr*/ "Running 3DSBC Axial BSB Pi Power...\r\n"
	},
	{
		/*prof*/ { "raman_radial_bsb_pi_pulse", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "3DSBC_TOP_BSB_RABI",
		/*infostr*/ "Running 3DSBC Top BSB Pi Power...\r\n"
	},
	{
		/*prof*/ { "shallow_trap_test", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "ERASURE_SURVIVAL",
		/*infostr*/ "Running earsure survival...\r\n"
	},
	{
		/*prof*/ { "raman_radial_spectroscopy_spillout", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
		/*filename*/ "ERASURE_COOLING",
		/*infostr*/ "Running erasure cooling...\r\n"
	},

//	{
//		/*prof*/ {"Automated-MOT-Temperature-Measurement", "MOT", MOT_ROUTINES_ADDRESS},
//		/*filename*/ "MOT_TEMPERATURE",
//		/*infostr*/ "Running Mot Temperature Calibration...\r\n"
//	},
//	{
//		/*prof*/ {"Automated-PGC-Temperature-Measurement", "PGC", PGC_ROUTINES_ADDRESS},
//		/*filename*/ "RED_PGC_TEMPERATURE",
//		/*infostr*/ "Running PGC Temperature Calibration...\r\n"
//	}
	//{
	//	/*prof*/ { "3DGSBC_Radial_Top_Sideband_Spectroscopy", "Atoms", PROFILES_PATH + "Standard_Calibrations\\Atoms" },
	//	/*filename*/ "3DSBC_RADIAL_TOP_SIDEBAND_RAMAN_SPECTROSCOPY",
	//	/*infostr*/ "Running 3DSBC Radial Top Raman Sideband Spectroscopy...\r\n"
	//},
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
