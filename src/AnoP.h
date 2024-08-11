#ifndef AnoP_H
#define AnoP_H
/* *************************************************************************
   @file       AnoP.h
   @project    AnoPlib
   @module     AnoPlib
   @brief      The library classes
   @date       25.04.2009
   @copyright  Daniel Krajzewicz
   @licence    LGPL
   @author     Daniel Krajzewicz
   @email      daniel@krajzewicz.de
   ------------------------------------------------------------------
    AnoPlib - small "animlet" library, see http://sf.net/projects/anoplib
    Copyright (C) 2009-2012 Daniel Krajzewicz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ------------------------------------------------------------------
   Remarks:
   ------------------------------------------------------------------
   ToDo:
 * *********************************************************************** */
/* =========================================================================
 * class definitions
 * ======================================================================= */
namespace AnoP {

    /** @class AnoPsystemBase
     * @brief A base class to allow template-free handling
     */
    class AnoPsystemBase {
    public:
        /// @brief Constructor
        AnoPsystemBase() {}

        /// @brief Destructor
        virtual ~AnoPsystemBase() {}

        /** @brief Renders all stored animlets, passing the given values to these
         * @param[in] timeDiff Assumed to be the time since last call
         * @param[in] something Further thing that will be passed during the rendering
         */
        virtual void renderAll(unsigned int timeDiff, void * const something) = 0;

    }; // AnoPsystemBase


    /** @class AnoPsystem
     * @brief Template-based realisation of the AnoPsystemBase
     */
    template<class T>
    class AnoPsystem : public AnoPsystemBase {
    public:
        /** @brief Constructor
         * @param[in] bufSize The initial buffer size
         */
        AnoPsystem(unsigned int bufSize=10) throw() :
            myAnimletNumber(0), myBufferSize(bufSize), myAnimletBuffer(new T[bufSize])
            { }


        /// @brief Destructor
        ~AnoPsystem() throw() { }


        /** @brief Renders all stored animlets, passing the given values to these
         *
         * At first "preRender" is called.
         *
         * Then, for each stored animlet the "render" method is called, passing the
         *  current animlet, the given time since last call, and the given additional
         *  data. In the case "render" returns false, "deleteAnimlet" is called.
         *  If "deleteAnimlet" returns true, the animlet is removed.
         *
         * At the end "postRender" is called.
         * 
         * @param[in] timeDiff Assumed to be the time since last call
         * @param[in] something Further thing that will be passed during the rendering
         */
        void renderAll(unsigned int timeDiff, void * const something) {
            preRender();
            for(unsigned int i=0; i<myAnimletNumber; ) {
                T &animlet = myAnimletBuffer[i];
                if(render(animlet, timeDiff, something)) {
                    ++i;
                    continue;
                }
                // animlet dies...
                if(deleteAnimlet(animlet)) {
                    myAnimletBuffer[i] = myAnimletBuffer[myAnimletNumber-1];
                    --myAnimletNumber;
                }
            }
            postRender();
        }


        /** @brief Adds an animlet to the list of those to render
         * @brief animlet The animlet to add
         */
        void addAnimlet(T &animlet) throw() {
            if(myAnimletNumber==myBufferSize) {
                int add = 10;
                T *newBuffer = new T[myBufferSize+add];
                memcpy(newBuffer, myAnimletBuffer, sizeof(T)*myBufferSize);
                std::swap(myAnimletBuffer, newBuffer);
                myBufferSize += add;
                delete[] newBuffer;
            }
            myAnimletBuffer[myAnimletNumber] = animlet;
            ++myAnimletNumber;
        }

    
        /// @name Methods to override by realisation
        /// @{

        /** @brief Called before rendering the stored animlets
         *
         * This method is meant to do any kind of initialisation; does
         *  nothing per default.
         */
        virtual void preRender() throw() {}

        
        /** @brief Called after rendering the stored animlets
         *
         * This method is meant to do any kind of cleaning up; does
         *  nothing per default.
         */
        virtual void postRender() throw() {}

        
        /** @brief Called for rendering a single animlet
         *
         * This method should do the rendering/animation and return whether the
         *  animlet shall be kept (true) or not (false).
         *
         * @param[in] which The animlet to render
         * @param[in] timeDiff The time since last call
         * @param[in] something Something else (free for your purposes)
         * @return Whether the animlet shall be kept
         */
        virtual bool render(T &which, unsigned int timeDiff, void * const something) throw() { return false; }


        /** @brief Animlet deletion callback
         *
         * If this callback returns true, the animlet is removed from the list
         *  of animlets to render. In the case any memory shall be freed, this
         *  method is reponsible for doing this.
         *
         * Nonetheless, there may be some reason for not deleting the animlet
         *  but reinitialise it. This can be done in this method, too. false
         *  should be returned then, so that the animlet stays in the list of
         *  animlets to render.
         * 
         * @param[in] which The animlet to delete
         */
        virtual bool deleteAnimlet(T &which) throw() { return true; }
        /// @}
    

    protected:
        /// @brief The number of currently running animlets
        unsigned int myAnimletNumber;

        /// @brief The number of allocated animlets
        unsigned int myBufferSize;

        /// @brief The allocated animlets
        T *myAnimletBuffer;


    }; // AnoPsystem


}; // AnoP


/* *********************************************************************** */
#endif
