/**
* Facebook Internet Explorer Toolbar Software License 
* Copyright (c) 2009 Facebook, Inc. 
*
* Permission is hereby granted, free of charge, to any person or organization
* obtaining a copy of the software and accompanying documentation covered by
* this license (which, together with any graphical images included with such
* software, are collectively referred to below as the "Software") to (a) use,
* reproduce, display, distribute, execute, and transmit the Software, (b)
* prepare derivative works of the Software (excluding any graphical images
* included with the Software, which may not be modified or altered), and (c)
* permit third-parties to whom the Software is furnished to do so, all
* subject to the following:
*
* The copyright notices in the Software and this entire statement, including
* the above license grant, this restriction and the following disclaimer,
* must be included in all copies of the Software, in whole or in part, and
* all derivative works of the Software, unless such copies or derivative
* works are solely in the form of machine-executable object code generated by
* a source language processor.  
*
* Facebook, Inc. retains ownership of the Software and all associated
* intellectual property rights.  All rights not expressly granted in this
* license are reserved by Facebook, Inc.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
* SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
* FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#ifndef NOTIFIER_POPUP_H
#define NOTIFIER_POPUP_H

#include "../common/GenericHtmlView.h"

namespace facebook {


/**
 * class NotifierPopup
 *
 * Shows popup window with notification content and picture.
 * Uses GenericHtmlView to display rich notification content 
 * Popup window is visible for kNotifTimeout milliseconds
 * Also this class counts popup instances and calculates
 * position, where to show next popup
 * 
 */
class NotifierPopup : public CWnd {

  DECLARE_DYNAMIC(NotifierPopup)

  // construction/destruction
 private:
  //do not allow create empty popups
  NotifierPopup() {};

 public:
  NotifierPopup(const String& url, const String& src, const String& msg);
  virtual ~NotifierPopup(void) {}

  // public methods
 public:
  /**
   * Adds instance of new popup window
   *
   * @param url - url to open
   * @param src - url to popup image
   * @param msg - message to show in popup
   *
   * @return new popup window instance
   */
  static void addInstance(const String& url, const String& src, const String& msg);


 protected:
  DECLARE_MESSAGE_MAP()
  
 protected:

  /**
   * Closes curent popup
   *
   */

  void closeIt();


  /**
   * Creates popup window
   *
   */
  BOOL create();
  
  /**
   * initialize html view
   *
   *
   * @return void
   */
  void initView();

  /**
   * Handles actions from html view - opens default web browser,
   * navigate it to url_ field value and closes popup window
   *
   * @param   url - not used
   * @param   cancelAction - not used
   * @param   notifyWindow - 
   *
   * @return position of the notification popup window
   */
  static bool handleHtmlLoad(LPCTSTR url, BOOL* cancelAction, CWnd* notifyWindow);

  // private methods
 private:

  /**
   * Calculates window rect of the notification popup window
   *
   * @return position of the notification popup window
   */

  CRect calculateWindowRect() const;

  /**
   * Calculates position of the notification popup window
   *
   * @return position of the notification popup window
   */

  CRect calculatePositionRect() const;
  
  /**
   * Closes popup when left mouse button clicked
   *
   * @param   window pointer
   *
   */
  
  afx_msg void OnLButtonUp(UINT, CPoint cp);

  /**
   * Closes popup window on timer notification
   *
   * @param   ID of Event
   *
   */
  
  afx_msg void OnTimer(UINT nIDEvent);


  /**
   * onNotifierLoad - closes popup window on time notification
   *
   * @param   wParam - windows message parameter
   * @param   lParam - windows message parameter
   *
   * @return LRESULT
   */
  
  afx_msg LRESULT onNotifierLoad(WPARAM wParam, LPARAM lParam);

 private:
  static long isEmptyCounter_; // check if at least one popup window is on the screen
  static long counter_; // counter of opened popup windows
  
  GenericHtmlView* popupHtmlView_; // html view with notifier content   

  String url_; // url to open when user clicked on popup 
  String src_; // url to notifier image 
  String msg_; // message to show in notifier popup
};


} // !namespace facebook

#endif //NOTIFIER_POPUP_H