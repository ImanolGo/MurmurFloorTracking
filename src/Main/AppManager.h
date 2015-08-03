/*
 *  AppManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#pragma once

#include "ofMain.h"

#include "Manager.h"

#include "SettingsManager.h"
#include "LayoutManager.h"
#include "TrackingManager.h"
#include "GuiManager.h"
#include "ResourceManager.h"
#include "VisualEffectsManager.h"
#include "ViewManager.h"
#include "KeyboardManager.h"
#include "OscManager.h"
#include "PaperThrowerManager.h"

//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //==========================================================================

    //! Returns the settings manager
    SettingsManager& getSettingsManager() { return m_settingsManager; }
    
    //! Returns the  tracking manager
    TrackingManager& getTrackingManager() { return m_trackingManager; }
    
    //! Returns the GUI manager
    GuiManager&  getGuiManager() { return m_guiManager; }
    
    //! Returns the resource manager
    ResourceManager&  getResourceManager() { return m_resourceManager; }
    
    //! Returns the view manager
    ViewManager&  getViewManager() { return m_viewManager; }
    
    //! Returns the visual effects manager
    VisualEffectsManager&  getVisualEffectsManager() { return m_visualEffectsManager; }
    
    //! Returns the  keyboard manager
    KeyboardManager&  getKeyboardManager() { return m_keyboardManager; }
    
    //! Returns the  OSC manager
    OscManager&  getOscManager() { return m_oscManager; }
    
    //! Returns the  paper thrower manager
    PaperThrowerManager&  getPaperThrowerManager() { return m_paperThrowerManager; }

    
    //==========================================================================
    
    void toggleDebugMode();
    
    void setDebugMode(bool showDebug);
    

private:

     //! Constructor
     AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Set-up all the managers
    void setupManagers();

    //! Set-up openFrameworks
    void setupOF();

    //! update all the managers
    void updateManagers();


private:

    SettingsManager                 m_settingsManager;          ///< Manages the application's settings
    LayoutManager                   m_layoutManager;            ///< Manages the layout
    TrackingManager                 m_trackingManager;          ///< Manages the camera tracking
    GuiManager                      m_guiManager;               ///< Manages the graphical user interface
    ResourceManager                 m_resourceManager;          ///< Manages the resources
    ViewManager                     m_viewManager;              ///< Manages the visuals
    VisualEffectsManager            m_visualEffectsManager;     ///< Manages the visual effects
    OscManager                      m_oscManager;               ///< Manages the OSC messages
    KeyboardManager                 m_keyboardManager;          ///< Manages the keboard input
    PaperThrowerManager             m_paperThrowerManager;      ///< Manages the paper thrower

    bool                            m_debugMode;
};

//==========================================================================


