/*
 *  VisualEffectsManager.cpp
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#include "VisualEffectsManager.h"

VisualEffectsManager::VisualEffectsManager(): Manager()
{
	// intentionally left empty
}


VisualEffectsManager::~VisualEffectsManager()
{
    ofLogNotice() <<"VisualEffectsManager::destructor";
}


void VisualEffectsManager::setup()
{
	if(m_initialized)
        return;

    Manager::setup();

    ofLogNotice() <<"VisualEffectsManager::initialized";
}

void VisualEffectsManager::update()
{
    for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();)
    {
        (*it)->update();
        
        if((*it)->isFinished()) {
            it = m_visualEffects.erase(it);
        }
        else{
            ++it;
        }
    }
}

void VisualEffectsManager::addVisualEffect(ofPtr<VisualEffect> visualEffect)
{
    if(!visualEffect)
        return;

	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();it++) {
		if(*it == visualEffect) {
			return;
		}
	}
	m_visualEffects.push_back(visualEffect);
}

void VisualEffectsManager::removeVisualEffect(ofPtr<VisualEffect> visualEffect)
{
    if(!visualEffect)
        return;

	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();)
    {
		if(*it == visualEffect) {
			it = m_visualEffects.erase(it);
		}
        else{
            ++it;
        }
	}
}

void VisualEffectsManager::removeAllVisualEffects(ofPtr<BasicVisual> visual)
{
	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
		if((*it)->getVisual() == visual) {
			it = m_visualEffects.erase(it);
		}
		else {
			++it;
		}
	}
}

void VisualEffectsManager::removeVisualEffects(ofPtr<BasicVisual> visual, const string& visualEffectName)
{
	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
		if((*it)->getVisual() == visual && (*it)->getName() == visualEffectName) {
			it = m_visualEffects.erase(it);
		}
		else {
			++it;
		}
	}
}

void VisualEffectsManager::createFadeEffect(ofPtr<BasicVisual> visual, double startAlpha,double endAlpha, double startAnimation, double animationTime)
{
    if(!visual)
        return;

	ofPtr<FadeVisual> fadeVisual = ofPtr<FadeVisual>(new FadeVisual(visual,QUINTIC,EASE_OUT));
	fadeVisual->setParameters(startAlpha,endAlpha,animationTime);
	fadeVisual->start(startAnimation);
	this->addVisualEffect(fadeVisual);
}

void VisualEffectsManager::createScaleEffect(ofPtr<BasicVisual> visual, const ofVec2f& startScale,const ofVec2f& endScale, double startAnimation, double animationTime)
{
    if(!visual)
        return;

	ofPtr<ScaleVisual> scaleVisual = ofPtr<ScaleVisual>(new ScaleVisual(visual,QUINTIC, EASE_OUT));
	scaleVisual->setParameters(startScale,endScale,animationTime);
	scaleVisual->start(startAnimation);
	this->addVisualEffect(scaleVisual);
}

void VisualEffectsManager::createScaleEffect(ofPtr<BasicVisual> visual, const ofVec2f& endScale, double startAnimation, double animationTime)
{
    if(!visual)
        return;

	ofPtr<ScaleVisual> scaleVisual = ofPtr<ScaleVisual>(new ScaleVisual(visual,QUINTIC, EASE_OUT));
	scaleVisual->setParameters(endScale,animationTime);
	scaleVisual->start(startAnimation);
	this->addVisualEffect(scaleVisual);
}

void VisualEffectsManager::popUpAnimation(ofPtr<BasicVisual> visual, double startAnimation, double animationTime)
{
    if(!visual)
        return;

    ofVec3f startScale(0,0,0);
    ofVec3f endScale(1,1,1);

	ofPtr<ScaleVisual> scaleVisual = ofPtr<ScaleVisual>(new ScaleVisual(visual,QUADRATIC, EASE_OUT));
	scaleVisual->setParameters(startScale,endScale*1.1,animationTime*0.5);
	scaleVisual->start(startAnimation);
	this->addVisualEffect(scaleVisual);

	scaleVisual = ofPtr<ScaleVisual>(new ScaleVisual(visual, QUADRATIC, EASE_OUT));
	scaleVisual->setParameters(endScale*1.1,endScale,animationTime*0.5);
	scaleVisual->start(startAnimation+animationTime*0.5);
	this->addVisualEffect(scaleVisual);
}

void VisualEffectsManager::createMoveEffect(ofPtr<BasicVisual> visual, const ofVec3f& startPos,const ofVec3f& endPos, double startAnimation, double animationTime)
{
    if(!visual)
        return;

	ofPtr<MoveVisual> moveVisual = ofPtr<MoveVisual>(new MoveVisual(visual,QUINTIC, EASE_OUT));
	moveVisual->setParameters(startPos,endPos,animationTime);
	moveVisual->start(startAnimation);
	this->addVisualEffect(moveVisual);
}

void VisualEffectsManager::createMoveEffect(ofPtr<BasicVisual> visual, const ofVec3f& endPos, double startAnimation, double animationTime)
{
    if(!visual)
        return;

	ofPtr<MoveVisual> moveVisual = ofPtr<MoveVisual>(new MoveVisual(visual,SINUSOIDAL, EASE_OUT));
	moveVisual->setParameters(endPos,animationTime);
	moveVisual->start(startAnimation);
	this->addVisualEffect(moveVisual);
}


void VisualEffectsManager::createColorEffect(ofPtr<BasicVisual> visual,const ofColor& startColor,const ofColor& endColor, double startAnimation, double animationTime)
{
    if(!visual)
        return;

	ofPtr<ColorEffect> colorEffect = ofPtr<ColorEffect>(new ColorEffect(visual,SINUSOIDAL, EASE_OUT));
	colorEffect->setParameters(startColor,endColor,animationTime);
	colorEffect->start(startAnimation);
	this->addVisualEffect(colorEffect);
}

void VisualEffectsManager::createColorEffect(ofPtr<BasicVisual> visual, const ofColor& endColor, double startAnimation, double animationTime)
{
    if(!visual)
        return;
    
    ofPtr<ColorEffect> colorEffect = ofPtr<ColorEffect>(new ColorEffect(visual,SINUSOIDAL, EASE_OUT));
    colorEffect->setParameters(endColor,animationTime);
    colorEffect->start(startAnimation);
    this->addVisualEffect(colorEffect);
}







