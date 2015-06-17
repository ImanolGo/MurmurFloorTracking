/*
 *  VisualEffectsManager.h
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#pragma once

#include "../Main/Manager.h"
#include "VisualEffects.h"
#include "BasicVisual.h"


//========================== class VisualEffectsManager ==============================
//============================================================================
/** \class VisualEffectsManager VisualEffectsManager.h
 *	\brief Manages arbitrary visual effects.
 *	\details Manages all different image effects.
 *   The animations are organized in fadeIn, fadeOut, move and bouncing effects.
 */
//==============================================================================

class VisualEffectsManager: public Manager
{
public:

    //! Constructor
    VisualEffectsManager();

    //! Destructor
    ~VisualEffectsManager();

    //! Set-ups the visual manager
	void setup();

    //! Updates all the visual effects
	void update();

	//! Removes a certain visual effect from the list
	void removeVisualEffect(ofPtr<VisualEffect>  visualEffect);
    

	//! Removes all visual effects for the specified visual
	void removeAllVisualEffects(ofPtr<BasicVisual> visual);

	//! Removes all visual effects for the specified visual and visual effect
	void removeVisualEffects(ofPtr<BasicVisual> visual, const string& visualEffectName);


    //==========================================================================

    //! Creates a certain fading visual effect
	void createFadeEffect(ofPtr<BasicVisual> visual, double startAlpha,double endAlpha, double startAnimation, double animationTime);

	//! Creates a certain scaling visual effect
	void createScaleEffect(ofPtr<BasicVisual> visual, const ofVec2f& startScale,const ofVec2f& endScale, double startAnimation, double animationTime);

	//! Creates a certain scaling visual effect
	void createScaleEffect(ofPtr<BasicVisual> visual, const ofVec2f& endScale, double startAnimation, double animationTime);

	//! Creates a certain moving visual effect
	void createMoveEffect(ofPtr<BasicVisual> visual, const ofVec3f& startPos,const ofVec3f& endPos, double startAnimation, double animationTime);

	//! Creates a certain moving visual effect
	void createMoveEffect(ofPtr<BasicVisual> visual, const ofVec3f& endPos, double startAnimation, double animationTime);

    //! Creates a certain color visual effect
    void createColorEffect(ofPtr<BasicVisual> visual, const ofColor& endColor, double startAnimation, double animationTime);
    
	//! Creates a certain color visual effect
	void createColorEffect(ofPtr<BasicVisual> visual,const ofColor& startColor,const ofColor& endColor, double startAnimation, double animationTime);

	//! Creates a certain color visual effect
	void popUpAnimation(ofPtr<BasicVisual> visual, double startAnimation, double animationTime);

private:

    //! Adds a certain visual effect
	void addVisualEffect(ofPtr<VisualEffect> visualEffect);

private:

    typedef std::vector< ofPtr<VisualEffect> >		VisualEffectVector;

	VisualEffectVector	m_visualEffects; ///< Vector of all visual effects

};

