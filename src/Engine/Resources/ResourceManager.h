/*
 *  ResourceManager.h

 *
 *  Created by Imanol Gomez on 16/02/15.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxSvg.h"


//==============================================================================
/** \class ResourceManager ResourceManager.h
*	\brief Manages ofTexture.
*	\details Manages loading and unloading of all resources.
*/
//==============================================================================


class ResourceManager: public Manager
{
    static const int DEFAULT_IMAGE_SIZE;    ///! Defines the default image size to be allocated

	public:

		//! Constructor.
        ResourceManager();
		//! Destructor.
        ~ResourceManager();

		//! Initializes the resource manager.
		void setup();

        //! Searches for the specified texture name and returns the first found.
        ofPtr<ofTexture> getTexture(const string& name) const;

        //! Searches for the specified SVG name and returns the first found.
        ofPtr<ofxSVG> getSVG(const string& name);

	private:

		//! Creates the default resource
		void createDefaultResource();

		//! Tells if the textures is already in the container
		bool containsTexture(const string& name) const;

		//! Tells if the svg is already in the container
		bool containsSvg(const string& name) const;

		//! Loads all the resources.
		void loadResources();

		//! Loads all the textures.
		void loadTextures();

		//! Loads all the SVG files.
		void loadSVGs();

	private:

		//======================= Typedefs =====================================

		typedef std::map< string, ofPtr<ofTexture> >	TextureMap;			///< holds a list of textures sorted by name
		typedef std::map< string, ofPtr<ofxSVG> >	    SvgMap;			    ///< holds a list of svgs sorted by name

		//======================================================================

		TextureMap		    m_textures;        ///< map of textures handles attached to a name
		SvgMap		        m_SVGs;            ///< map of SVGs handles attached to a name
		ofPtr<ofTexture>    m_defaultTexture;  ///< stores a default texture in case another resource cannot be loaded

};



