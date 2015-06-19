/*
 *  ResourceManager.cpp
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#include "AppManager.h"
#include "SettingsManager.h"

#include "ResourceManager.h"

const int ResourceManager::DEFAULT_IMAGE_SIZE = 256;


ResourceManager::ResourceManager() : Manager()
{
    //Intentionally left empty
}

ResourceManager::~ResourceManager()
{
    ofLogNotice() <<"ResourceManager::destructor" ;
}


void ResourceManager::setup()
{
    if(m_initialized)
		return;

    ofLogNotice() <<"ResourceManager::initialized" ;

	Manager::setup();

    this->createDefaultResource();
    this->loadResources();
}

void ResourceManager::loadResources()
{
    this->loadTextures();
    this->loadSVGs();
}

void ResourceManager::loadTextures()
{
    ResourcesPathMap texturePathMap = AppManager::getInstance().getSettingsManager().getTextureResourcesPath();

    for(ResourcesPathMap::iterator it = texturePathMap.begin(); it!= texturePathMap.end(); it++)
    {
        string textureName = it->first;
        string texturePath = it->second;

        ofTexture texture;

        if(ofLoadImage(texture,texturePath)){
            m_textures[textureName] = texture;
            ofLogNotice() <<"ResourceManager::loadTextures-> allocated texture " << textureName ;

        }
        else{
            ofLogNotice() <<"ResourceManager::loadTextures-> unable to load texture " << textureName
            << " from path " << texturePath ;
        }
    }
}

void ResourceManager::loadSVGs()
{
    ResourcesPathMap svgPathMap = AppManager::getInstance().getSettingsManager().getSvgResourcesPath();

    for(ResourcesPathMap::iterator it = svgPathMap.begin(); it!= svgPathMap.end(); it++)
    {
        string svgName = it->first;
        string svgPath = it->second;

        ofxSVG svg;
        svg.load(svgPath);
        m_SVGs[svgName] = svg;
        ofLogNotice() <<"ResourceManager::loadSVGs-> allocated svg " << svgName ;
    }
}


const ofTexture& ResourceManager::getTexture(const string& name) const
{
    if(this->containsTexture(name)) {
        return m_textures.at(name);
	}

	return m_defaultTexture;
}
void ResourceManager::createDefaultResource()
{
    int resourceSize = 256;
    m_defaultTexture.allocate(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE,GL_RGB);
}

bool ResourceManager::containsTexture(const string& name) const
{
	if(m_textures.find(name) == m_textures.end()) {
        ofLogNotice() <<"ResourceManager::containsTexture-> no resource with name " << name ;
		return false; // no entries for the specified name
	}

	return true;
}


const ofxSVG& ResourceManager::getSVG(const string& name)
{
    if(this->containsSvg(name)) {
		return m_SVGs.at(name);
	}

	return m_defaultSVG;
}

bool ResourceManager::containsSvg(const string& name) const
{
	if(m_SVGs.find(name) == m_SVGs.end()) {
        ofLogNotice() <<"ResourceManager::containsSvg-> no resource with name " << name ;
		return false; // no entries for the specified name
	}

	return true;
}






