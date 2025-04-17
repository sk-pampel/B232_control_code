// created by Mark O. Brown
#include "stdafx.h"
#include "AiSystem.h"
#include <qtimer.h>
#include <iostream>
#include <thread>
#include <chrono>

AiSystem::AiSystem( ) : daqmx( ANALOG_IN_SAFEMODE ) {
}

/*
 *	We use a PCI card for analog input currently.
 */
void AiSystem::initDaqmx( ){
	daqmx.createTask( "Analog-Input", analogInTask0 );
	daqmx.createAiVoltageChan( analogInTask0, cstr(boardName + "/ai0:7"), "", DAQmx_Val_Diff, -10.0, 10.0, DAQmx_Val_Volts, nullptr );
}


std::string AiSystem::getSystemStatus( ){
	long answer = daqmx.getProductCategory( cstr(boardName) );
	std::string answerStr = "AI System: Connected... device category = " + str( answer );
	return answerStr;
}


void AiSystem::refreshDisplays( ){
	for ( auto dispInc : range(voltDisplays.size())){
		voltDisplays[dispInc]->setText( str(currentValues[dispInc], 4).c_str() );
	}
}


void AiSystem::initialize (QPoint& loc, IChimeraQtWindow* parent) {
	auto& px = loc.rx (), & py = loc.ry ();
	initDaqmx ();
	title = new QLabel ("ANALOG-INPUT", parent);
	title->setGeometry ({ QPoint{px, py}, QPoint{px + 480, py += 25} });

	getValuesButton = new CQPushButton ("Get Values", parent);
	getValuesButton->setGeometry (px, py, 160, 25);
	parent->connect (getValuesButton, &QPushButton::released, [this]() { refreshCurrentValues (); refreshDisplays (); });
	px += 160;
	continuousQueryCheck = new CQCheckBox ("Qry Cont.", parent);
	continuousQueryCheck->setGeometry (px, py, 160, 25);
	px += 160;
	queryBetweenVariations = new CQCheckBox ("Qry Btwn Vars", parent);
	queryBetweenVariations->setGeometry (px, py, 160, 25);
	py += 25;
	px -= 320; 
	continuousIntervalLabel = new QLabel ("Cont. Interval:", parent);
	continuousIntervalLabel->setGeometry (px, py, 160, 20);
	continuousInterval = new CQLineEdit (qstr (AiSettings ().continuousModeInterval), parent);
	continuousInterval->setGeometry (px + 160, py, 80, 20);
	QTimer::singleShot (1000, this, &AiSystem::handleTimer);
	avgNumberLabel = new QLabel ("# To Avg:", parent);
	avgNumberLabel->setGeometry (px + 240, py, 160, 20);

	avgNumberEdit = new CQLineEdit (qstr (AiSettings ().numberMeasurementsToAverage), parent);
	avgNumberEdit->setGeometry (px + 400, py, 80, 20);
	py += 20;
	// there's a single label first, hence the +1.
	long dacInc = 0, collumnInc = 0, numCols=4;
	long colSize = long(480 / numCols);
	for ( auto& disp : voltDisplays ){
		if ( dacInc == (collumnInc + 1) * NUMBER_AI_CHANNELS / numCols ){	// then next column. 
			collumnInc++;
			py -= 20 * NUMBER_AI_CHANNELS / numCols;
		}
		disp = new QLabel ("0", parent);
		disp->setGeometry (px + 20 + collumnInc * colSize, py, colSize-20, 20);
		py += 20;
		dacInc++;
	}
	collumnInc = 0;
	py -= long(20 * voltDisplays.size( ) / numCols);

	for ( auto dacInc : range( NUMBER_AI_CHANNELS ) ){
		auto& label = dacLabels[dacInc];
		if ( dacInc == (collumnInc + 1) * NUMBER_AI_CHANNELS / numCols)	{	// then next column
			collumnInc++;
			py -= 20 * NUMBER_AI_CHANNELS / numCols;
		}
		label = new QLabel (cstr (dacInc), parent);
		label->setGeometry (px + collumnInc * colSize, py, 20, 20);
		QFont font = label->font ();
		font.setUnderline (true);
		label->setFont (font);
		py += 20;
	}
}

void AiSystem::handleTimer () {
	int interval = 1000;
	try {
		if (continuousQueryCheck->isChecked ()) {
			refreshCurrentValues ();
			refreshDisplays ();
		}
		try {
			interval = boost::lexical_cast<int>(str (continuousInterval->text ()));
		}
		catch (boost::bad_lexical_cast&) { // just go with 1s if the input is invalid.
		}
	}
	catch (ChimeraError & err) {
		errBox (err.trace ());
	}
	QTimer::singleShot (interval, this, &AiSystem::handleTimer);
}

AiSettings AiSystem::getAiSettings (){
	AiSettings settings;
	settings.queryBtwnVariations = queryBetweenVariations->isChecked ();
	settings.queryContinuously = continuousQueryCheck->isChecked ();
	try{
		settings.continuousModeInterval = boost::lexical_cast<int>(str(continuousInterval->text()));
	}
	catch (ChimeraError &) { errBox ("Failed to convert ai-system number of measurements to average string to int!"); };
	try{
		settings.numberMeasurementsToAverage = boost::lexical_cast<unsigned>(str(avgNumberEdit->text()));
		if (settings.numberMeasurementsToAverage < 2){
			settings.numberMeasurementsToAverage = 2;
			setAiSettings (settings);
		}
	}
	catch (ChimeraError &) { errBox ("Failed to convert ai-system number of measurements to average string to unsigned int!"); };
	return settings;
}

AiSettings AiSystem::getSettingsFromConfig (ConfigStream& file){
	AiSettings settings;
	file >> settings.queryBtwnVariations;
	file >> settings.queryContinuously;
	file >> settings.numberMeasurementsToAverage;
	file >> settings.continuousModeInterval;
	return settings;
}

void AiSystem::handleSaveConfig (ConfigStream& file){
	auto settings = getAiSettings ();
	file << configDelim 
		<< "\n/*Query Between Variations?*/ " << settings.queryBtwnVariations 
		<< "\n/*Query Continuously?*/ " << settings.queryContinuously 
		<< "\n/*Average Number:*/ " << settings.numberMeasurementsToAverage 
		<< "\n/*Contiuous Mode Interval:*/ " << settings.continuousModeInterval 
		<< "\nEND_" + configDelim + "\n";
}

void AiSystem::setAiSettings (AiSettings settings){
	queryBetweenVariations->setChecked (settings.queryBtwnVariations);
	continuousQueryCheck->setChecked (settings.queryContinuously);
	avgNumberEdit->setText (qstr(settings.numberMeasurementsToAverage));
	continuousInterval->setText (qstr (settings.continuousModeInterval));
}


bool AiSystem::wantsContinuousQuery( ){
	return continuousQueryCheck->isChecked( );
}


//void AiSystem::refreshCurrentValues( ){
//	currentValues = getSingleSnapArray( getAiSettings().numberMeasurementsToAverage );
//}

void AiSystem::refreshCurrentValues() {
	try {
		std::vector<float64> snap = getSingleSnap(100); // Example n_to_avg, adjust as needed
		if (snap.size() == NUMBER_AI_CHANNELS) {
			std::lock_guard<std::mutex> lock(aiMutex); // Protect vector modifications
			resVals.insert(resVals.end(), snap.begin(), snap.end()); // Add all elements of snap
			ctrlVals.insert(ctrlVals.end(), snap.begin(), snap.end()); // Use snap for now, adjust if needed
			std::cout << "Added snap to resVals and ctrlVals, sizes: " << resVals.size() << ", " << ctrlVals.size() << std::endl;
		}
		else {
			std::cout << "Warning: Incomplete snap data, size = " << snap.size() << ", skipped." << std::endl;
		}
	}
	catch (ChimeraError & err) {
		std::cout << "Error in refreshCurrentValues: " << err.trace() << ", skipping update." << std::endl;
	}
}

//void AiSystem::refreshCurrentValues() {
//	std::cout << "Before adding data: currentValues size = " << currentValues.size() << std::endl;
//
//	currentValues = getSingleSnapArray(getAiSettings().numberMeasurementsToAverage);
//
//	std::cout << "After adding data: currentValues size = " << currentValues.size() << std::endl;
//}


void AiSystem::armAquisition( unsigned numSnapshots ){
	// may need to use numSnapshots X NUM_AI_CHANNELS?
	daqmx.configSampleClkTiming( analogInTask0, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, numSnapshots );
	daqmx.startTask( analogInTask0 );
	aquisitionData = std::vector<float64>( NUMBER_AI_CHANNELS * numSnapshots );
}

std::vector<float64> AiSystem::getCurrentValues( ){
	return { currentValues.begin( ), currentValues.end( ) };
}

void AiSystem::getAquisitionData( ){
	int32 sampsRead;
	daqmx.readAnalogF64( analogInTask0, aquisitionData, sampsRead );
}

bool AiSystem::wantsQueryBetweenVariations( ){
	return queryBetweenVariations->isChecked( );
}

//std::vector<float64> AiSystem::getSingleSnap( unsigned n_to_avg ){
//	try{
//		daqmx.configSampleClkTiming( analogInTask0, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, n_to_avg );
//		daqmx.startTask( analogInTask0 );
//		// don't understand why but need 2 samples min???
//		std::vector<float64> tmpdata( NUMBER_AI_CHANNELS*n_to_avg );
//		int32 sampsRead;
//		daqmx.readAnalogF64( analogInTask0, tmpdata, sampsRead );
//		//int32 sampsRead = 0;
//		//daqmx.readAnalogF64(analogInTask0, tmpdata, &sampsRead);
//
//		daqmx.stopTask( analogInTask0 );
//		std::vector<float64> data( NUMBER_AI_CHANNELS );
//		unsigned count = 0;
//		for ( auto& d : data ){
//			d = 0;
//			for ( auto i : range( n_to_avg ) ){
//				d += tmpdata[count++];
//			}
//			d /= n_to_avg;
//		}
//		return data;
//	}
//	catch (ChimeraError &){
//		throwNested ("Error exception thrown while getting Ai system single snap!");
//	}
//}

std::vector<float64> AiSystem::getSingleSnap(unsigned n_to_avg) {
	std::lock_guard<std::mutex> lock(aiMutex); // Lock mutex
	std::cout << "Entering getSingleSnap with n_to_avg = " << n_to_avg << std::endl;
	try {
		std::cout << "Checking and stopping task if running..." << std::endl;
		daqmx.ensureTaskStopped(analogInTask0);

		std::cout << "Configuring sample clock timing..." << std::endl;
		daqmx.configSampleClkTiming(analogInTask0, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, n_to_avg);

		std::cout << "Starting task..." << std::endl;
		daqmx.startTask(analogInTask0);

		std::cout << "Allocating tmpdata vector (size = " << NUMBER_AI_CHANNELS * n_to_avg << ")..." << std::endl;
		std::vector<float64> tmpdata(NUMBER_AI_CHANNELS * n_to_avg);
		int32 sampsRead;
		std::cout << "Reading analog data..." << std::endl;
		daqmx.readAnalogF64(analogInTask0, tmpdata, sampsRead);

		std::cout << "Read " << sampsRead << " samples. Stopping task..." << std::endl;
		daqmx.stopTask(analogInTask0);
		std::cout << "Adding 20ms delay after stop..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		std::cout << "Processing averaged data..." << std::endl;
		std::vector<float64> data(NUMBER_AI_CHANNELS);
		unsigned count = 0;
		for (auto& d : data) {
			d = 0;
			for (auto i : range(n_to_avg)) {
				d += tmpdata[count++];
			}
			d /= n_to_avg;
		}
		std::cout << "Returning averaged data (size = " << data.size() << ")..." << std::endl;
		return data;
	}
	catch (ChimeraError & err) {
		std::cout << "ChimeraError caught: " << err.trace() << std::endl;
		throwNested("Error exception thrown while getting Ai system single snap!");
	}
	catch (...) {
		std::cout << "Unknown exception caught in getSingleSnap!" << std::endl;
		throwNested("Unknown error in getSingleSnap!");
	}
}

double AiSystem::getSingleChannelValue( unsigned chan, unsigned n_to_avg ){
	auto all = getSingleSnap( n_to_avg );
	return all[chan];
}


std::array<float64, AiSystem::NUMBER_AI_CHANNELS> AiSystem::getSingleSnapArray( unsigned n_to_avg ){
	std::vector<float64> data = getSingleSnap( n_to_avg );
	std::array<float64, NUMBER_AI_CHANNELS> retData;
	for ( auto dataInc : range( NUMBER_AI_CHANNELS ) ){
		retData[dataInc] = data[dataInc];
	}
	return retData;
}

//#include <iostream> // Include for debugging output
//
//std::array<float64, AiSystem::NUMBER_AI_CHANNELS> AiSystem::getSingleSnapArray(unsigned n_to_avg) {
//	std::vector<float64> data = getSingleSnap(n_to_avg);
//
//	// Print the contents of data
//	std::cout << "getSingleSnap(" << n_to_avg << ") returned: ";
//	for (const auto& val : data) {
//		std::cout << val << " ";
//	}
//	std::cout << std::endl;
//
//	std::array<float64, NUMBER_AI_CHANNELS> retData;
//	for (size_t dataInc = 0; dataInc < NUMBER_AI_CHANNELS; ++dataInc) {
//		retData[dataInc] = data[dataInc];
//	}
//
//	return retData;
//}


void AiSystem::logSettings (DataLogger& log, ExpThreadWorker* threadworker){
}
