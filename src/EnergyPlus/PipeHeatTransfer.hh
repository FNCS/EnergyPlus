// EnergyPlus, Copyright (c) 1996-2016, The Board of Trustees of the University of Illinois and
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy). All rights
// reserved.
//
// If you have questions about your rights to use or distribute this software, please contact
// Berkeley Lab's Innovation & Partnerships Office at IPO@lbl.gov.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without Lawrence Berkeley National Laboratory's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// You are under no obligation whatsoever to provide any bug fixes, patches, or upgrades to the
// features, functionality or performance of the source code ("Enhancements") to anyone; however,
// if you choose to make your Enhancements available either publicly, or directly to Lawrence
// Berkeley National Laboratory, without imposing a separate written license agreement for such
// Enhancements, then you hereby grant the following license: a non-exclusive, royalty-free
// perpetual license to install, use, modify, prepare derivative works, incorporate into other
// computer software, distribute, and sublicense such enhancements or derivative works thereof,
// in binary and source code form.

#ifndef PipeHeatTransfer_hh_INCLUDED
#define PipeHeatTransfer_hh_INCLUDED

// C++ Headers
#include <memory>

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>
#include <ObjexxFCL/Array4D.hh>
#include <ObjexxFCL/Optional.hh>

// EnergyPlus Headers
#include <EnergyPlus.hh>
#include <DataGlobals.hh>
#include <GroundTemperatureModeling/GroundTemperatureModelManager.hh>

namespace EnergyPlus {

namespace PipeHeatTransfer {

	// Using/Aliasing
	using namespace GroundTemperatureManager;

	// Data
	// MODULE PARAMETER DEFINITIONS

	extern int const None;
	extern int const ZoneEnv;
	extern int const ScheduleEnv;
	extern int const OutsideAirEnv;
	extern int const GroundEnv;

	extern int const PreviousTimeIndex;
	extern int const CurrentTimeIndex;
	extern int const TentativeTimeIndex;

	extern Real64 const InnerDeltaTime; // one minute time step in seconds

	// DERIVED TYPE DEFINITIONS

	// the model data structures

	// MODULE VARIABLE DECLARATIONS:
	extern int NumOfPipeHT; // Number of Pipe Heat Transfer objects
	extern int InletNodeNum; // module variable for inlet node number
	extern int OutletNodeNum; // module variable for outlet node number
	extern int PipeHTNum; // object index
	extern Real64 MassFlowRate; // pipe mass flow rate
	extern Real64 VolumeFlowRate; // pipe volumetric flow rate
	extern Real64 DeltaTime; // time change from last update
	extern Real64 InletTemp; // pipe inlet temperature
	extern Real64 OutletTemp; // pipe outlet temperature
	extern Real64 EnvironmentTemp; // environmental temperature (surrounding pipe)
	extern Real64 EnvHeatLossRate; // heat loss rate from pipe to the environment
	extern Real64 FluidHeatLossRate; // overall heat loss from fluid to pipe
	extern bool GetPipeInputFlag; // First time, input is "gotten"
	extern int NumInnerTimeSteps; // the number of "inner" time steps for our model

	// SUBROUTINE SPECIFICATIONS FOR MODULE

	// Types

	struct PipeHTData
	{
		// Members
		// Input data
		std::string Name; // name of the component
		std::string Construction; // construction object name
		std::string Environment; // keyword:  'Schedule', 'OutdoorAir', 'Zone'
		std::string EnvrSchedule; // temperature schedule for environmental temp
		std::string EnvrVelSchedule; // temperature schedule for environmental temp
		std::string EnvrZone; // zone providing environmental temp
		std::string EnvrAirNode; // outside air node providing environmental temp
		Real64 Length; // total pipe length [m]
		Real64 PipeID; // pipe inside diameter [m]
		std::string InletNode; // inlet node name
		std::string OutletNode; // outlet node name
		int InletNodeNum; // inlet node number
		int OutletNodeNum; // outlet node number
		int TypeOf; // Type of pipe
		// derived data
		int ConstructionNum; // construction ref number
		int EnvironmentPtr;
		int EnvrSchedPtr; // pointer to schedule used to set environmental temp
		int EnvrVelSchedPtr; // pointer to schedule used to set environmental temp
		int EnvrZonePtr; // pointer to zone number used to set environmental temp
		int EnvrAirNodeNum; // pointer to outside air node used to set environmental temp
		int NumSections; // total number of nodes along pipe length
		Real64 FluidSpecHeat; // fluid Cp [J/kg.K]
		Real64 FluidDensity; // density [kg/m3]
		Real64 MaxFlowRate; // max flow rate (from loop/node data)
		Real64 FluidSectionVol; // volume of each pipe section (node) [m^3]
		Real64 InsideArea; // pipe section inside surface area [m^2]
		Real64 OutsideArea; // pipe section outside surface area [m^2]
		Real64 SectionArea; // cross sectional area [m^2]
		Real64 PipeHeatCapacity; // heat capacity of pipe section [J/m.K]
		Real64 PipeOD; // pipe outside diameter [m]
		Real64 PipeCp; // pipe materail Cp [J/kg.K]
		Real64 PipeDensity; // pipe material density [kg/m3]
		Real64 PipeConductivity; // pipe material thermal conductivity [W/m.K]
		Real64 InsulationOD; // insulation outside diameter [m]
		Real64 InsulationCp; // insulation  specific heat [J/kg.K]
		Real64 InsulationDensity; // insulation density [kg/m3]
		Real64 InsulationConductivity; // insulation conductivity [W/m.K]
		Real64 InsulationThickness; // insulation thickness [m]
		Real64 InsulationResistance; // Insulation thermal resistance [m2.K/W]
		Real64 CurrentSimTime; // Current simulation time [hr]
		Real64 PreviousSimTime; // simulation time the report data was last updated
		Array1D< Real64 > TentativeFluidTemp;
		Array1D< Real64 > FluidTemp; // arrays for fluid and pipe temperatures at each node
		Array1D< Real64 > PreviousFluidTemp;
		Array1D< Real64 > TentativePipeTemp;
		Array1D< Real64 > PipeTemp;
		Array1D< Real64 > PreviousPipeTemp;
		int NumDepthNodes; // number of soil grid points in the depth direction
		int PipeNodeDepth; // soil depth grid point where pipe is located
		int PipeNodeWidth; // soil width grid point where pipe is located
		Real64 PipeDepth; // pipe burial depth [m]
		Real64 DomainDepth; // soil grid depth [m]
		Real64 dSregular; // grid spacing in cartesian domain [m]
		Real64 OutdoorConvCoef; // soil to air convection coefficient [W/m2.K]
		std::string SoilMaterial; // name of soil material:regular object
		int SoilMaterialNum; // soil material index in material data structure
		int MonthOfMinSurfTemp; // month of minimum ground surface temperature
		Real64 MinSurfTemp; // minimum annual surface temperature [C]
		Real64 SoilDensity; // density of soil [kg/m3]
		Real64 SoilDepth; // thickness of soil [m]
		Real64 SoilCp; // specific heat of soil [J/kg.K]
		Real64 SoilConductivity; // thermal conductivity of soil [W/m.K]
		Real64 SoilRoughness; // ground surface roughness
		Real64 SoilThermAbs; // ground surface thermal absorptivity
		Real64 SoilSolarAbs; // ground surface solar absorptivity
		Real64 CoefS1; // soil surface finite difference coefficient
		Real64 CoefS2; // soil surface finite difference coefficient
		Real64 CoefA1; // soil finite difference coefficient
		Real64 CoefA2; // soil finite difference coefficient
		Real64 FourierDS; // soil Fourier number based on grid spacing
		Real64 SoilDiffusivity; // soil thermal diffusivity [m2/s]
		Real64 SoilDiffusivityPerDay; // soil thermal diffusivity [m2/day]
		Array4D< Real64 > T; // soil temperature array
		bool BeginSimInit; // begin sim and begin environment flag
		bool BeginSimEnvrn; // begin sim and begin environment flag
		bool FirstHVACupdateFlag;
		bool BeginEnvrnupdateFlag;
		bool SolarExposed; // Flag to determine if solar is included at ground surface
		Real64 SumTK; // Sum of thickness/conductivity over all material layers
		Real64 ZoneHeatGainRate; // Lagged energy summation for zone heat gain {W}
		int LoopNum; // PlantLoop index where this pipe lies
		int LoopSideNum; // PlantLoop%LoopSide index where this pipe lies
		int BranchNum; // ..LoopSide%Branch index where this pipe lies
		int CompNum; // ..Branch%Comp index where this pipe lies
		bool CheckEquipName;
		std::shared_ptr< BaseGroundTempsModel > groundTempModel;

		// Default Constructor
		PipeHTData() :
			Length( 0.0 ),
			PipeID( 0.0 ),
			InletNodeNum( 0 ),
			OutletNodeNum( 0 ),
			TypeOf( 0 ),
			ConstructionNum( 0 ),
			EnvironmentPtr( 0 ),
			EnvrSchedPtr( 0 ),
			EnvrVelSchedPtr( 0 ),
			EnvrZonePtr( 0 ),
			EnvrAirNodeNum( 0 ),
			NumSections( 0 ),
			FluidSpecHeat( 0.0 ),
			FluidDensity( 0.0 ),
			MaxFlowRate( 0.0 ),
			FluidSectionVol( 0.0 ),
			InsideArea( 0.0 ),
			OutsideArea( 0.0 ),
			SectionArea( 0.0 ),
			PipeHeatCapacity( 0.0 ),
			PipeOD( 0.0 ),
			PipeCp( 0.0 ),
			PipeDensity( 0.0 ),
			PipeConductivity( 0.0 ),
			InsulationOD( 0.0 ),
			InsulationCp( 0.0 ),
			InsulationDensity( 0.0 ),
			InsulationConductivity( 0.0 ),
			InsulationThickness( 0.0 ),
			InsulationResistance( 0.0 ),
			CurrentSimTime( 0.0 ),
			PreviousSimTime( 0.0 ),
			NumDepthNodes( 0 ),
			PipeNodeDepth( 0 ),
			PipeNodeWidth( 0 ),
			PipeDepth( 0.0 ),
			DomainDepth( 0.0 ),
			dSregular( 0.0 ),
			OutdoorConvCoef( 0.0 ),
			SoilMaterialNum( 0 ),
			MonthOfMinSurfTemp( 0 ),
			MinSurfTemp( 0.0 ),
			SoilDensity( 0.0 ),
			SoilDepth( 0.0 ),
			SoilCp( 0.0 ),
			SoilConductivity( 0.0 ),
			SoilRoughness( 0.0 ),
			SoilThermAbs( 0.0 ),
			SoilSolarAbs( 0.0 ),
			CoefS1( 0.0 ),
			CoefS2( 0.0 ),
			CoefA1( 0.0 ),
			CoefA2( 0.0 ),
			FourierDS( 0.0 ),
			SoilDiffusivity( 0.0 ),
			SoilDiffusivityPerDay( 0.0 ),
			BeginSimInit( true ),
			BeginSimEnvrn( true ),
			FirstHVACupdateFlag( true ),
			BeginEnvrnupdateFlag( true ),
			SolarExposed( true ),
			SumTK( 0.0 ),
			ZoneHeatGainRate( 0.0 ),
			LoopNum( 0 ),
			LoopSideNum( 0 ),
			BranchNum( 0 ),
			CompNum( 0 ),
			CheckEquipName( true )
		{}

	};

	struct PipeHeatTransferReport
	{
		// Members
		// Report data
		Real64 FluidInletTemp; // inlet temperature [C]
		Real64 FluidOutletTemp; // outlet temperature [C]
		Real64 MassFlowRate; // mass flow rate [kg/s]
		Real64 FluidHeatLossRate; // overall heat transfer rate from fluid to pipe [W]
		Real64 FluidHeatLossEnergy; // energy transferred from fluid to pipe [J]
		Real64 PipeInletTemp; // pipe temperature at inlet [C]
		Real64 PipeOutletTemp; // pipe temperature at Oulet [C]
		Real64 EnvironmentHeatLossRate; // overall heat transfer rate from pipe to environment [W]
		Real64 EnvHeatLossEnergy; // energy transferred from pipe to environment [J]
		Real64 VolumeFlowRate;

		// Default Constructor
		PipeHeatTransferReport() :
			FluidInletTemp( 0.0 ),
			FluidOutletTemp( 0.0 ),
			MassFlowRate( 0.0 ),
			FluidHeatLossRate( 0.0 ),
			FluidHeatLossEnergy( 0.0 ),
			PipeInletTemp( 0.0 ),
			PipeOutletTemp( 0.0 ),
			EnvironmentHeatLossRate( 0.0 ),
			EnvHeatLossEnergy( 0.0 ),
			VolumeFlowRate( 0.0 )
		{}

	};

	// Object Data
	extern Array1D< PipeHTData > PipeHT;
	extern Array1D< PipeHeatTransferReport > PipeHTReport;

	// Functions

	void
	SimPipesHeatTransfer(
		int const EquipType,
		std::string const & EquipName, // name of the Pipe Heat Transfer.
		int & EqNum, // index in local derived types for external calling
		bool const InitLoopEquip,
		bool const FirstHVACIteration // component number
	);

	//==============================================================================

	void
	PushInnerTimeStepArrays( int const PipeHTNum );

	void
	GetPipesHeatTransfer();

	void
	ValidatePipeConstruction(
		std::string const & PipeType, // module object of pipe (error messages)
		std::string const & ConstructionName, // construction name of pipe (error messages)
		std::string const & FieldName, // fieldname of pipe (error messages)
		int const ConstructionNum, // pointer into construction data
		int const PipeNum, // pointer into pipe data
		bool & ErrorsFound // set to true if errors found here
	);

	//==============================================================================

	void
	InitPipesHeatTransfer(
		int const PipeType,
		int const PipeHTNum, // component number
		bool const FirstHVACIteration // component number
	);

	//==============================================================================

	void
	InitializeHeatTransferPipes(
		int const PipeType, // Type of Pipe
		std::string const & PipeName, // Name of Pipe
		int & PipeNum // Index into pipe structure for name
	);

	//==============================================================================

	void
	CalcPipesHeatTransfer(
		int const PipeHTNum, // component number
		Optional_int_const LengthIndex = _
	);

	//==============================================================================

	void
	CalcBuriedPipeSoil( int const PipeHTNum ); // Current Simulation Pipe Number

	//==============================================================================

	void
	UpdatePipesHeatTransfer();

	//==============================================================================

	void
	ReportPipesHeatTransfer( int const PipeHTNum ); // Index for the surface under consideration

	//==============================================================================

	void
	CalcZonePipesHeatGain();

	//==============================================================================

	Real64
	CalcPipeHeatTransCoef(
		int const PipeHTNum,
		Real64 const Temperature, // Temperature of water entering the surface, in C
		Real64 const MassFlowRate, // Mass flow rate, in kg/s
		Real64 const Diameter // Pipe diameter, m
	);

	//==============================================================================

	Real64
	OutsidePipeHeatTransCoef( int const PipeHTNum ); // Index number of surface under consideration

	//==============================================================================

	Real64
	TBND(
		Real64 const z, // Current Depth
		Real64 const DayOfSim, // Current Simulation Day
		int const PipeHTNum // Current Pipe Number
	);

	//===============================================================================

	//===============================================================================

} // PipeHeatTransfer

} // EnergyPlus

#endif
