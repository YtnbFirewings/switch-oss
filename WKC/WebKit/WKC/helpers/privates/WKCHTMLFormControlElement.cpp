/*
 * Copyright (c) 2011-2015 ACCESS CO., LTD. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "config.h"

#include "helpers/WKCHTMLFormControlElement.h"
#include "helpers/privates/WKCHTMLFormControlElementPrivate.h"

#include "HTMLFormControlElement.h"
#include "helpers/privates/WKCHTMLFormElementPrivate.h"

namespace WKC {

HTMLFormControlElementPrivate::HTMLFormControlElementPrivate(WebCore::HTMLFormControlElement* parent)
    : HTMLElementPrivate(parent)
    , m_wkc(*this)
    , m_formElement(0)
{
}

HTMLFormControlElementPrivate::~HTMLFormControlElementPrivate()
{
    delete m_formElement;
}

WebCore::HTMLFormControlElement*
HTMLFormControlElementPrivate::webcore() const
{
    return static_cast<WebCore::HTMLFormControlElement*>(HTMLElementPrivate::webcore());
}

HTMLFormElement*
HTMLFormControlElementPrivate::form()
{
    WebCore::HTMLFormElement* form = webcore()->form();
    if (!form)
        return 0;
    if (!m_formElement || m_formElement->webcore() != form) {
        delete m_formElement;
        m_formElement = new HTMLFormElementPrivate(form);
    }
    return reinterpret_cast<HTMLFormElement*>(&m_formElement->wkc());
}

void
HTMLFormControlElementPrivate::dispatchFormControlInputEvent()
{
    webcore()->dispatchFormControlInputEvent();
}

void
HTMLFormControlElementPrivate::dispatchFormControlChangeEvent()
{
    webcore()->dispatchFormControlChangeEvent();
}

////////////////////////////////////////////////////////////////////////////////

HTMLFormControlElement::HTMLFormControlElement(HTMLFormControlElementPrivate& parent)
    : HTMLElement(parent)
{
}

void
HTMLFormControlElement::dispatchFormControlInputEvent()
{
    return static_cast<HTMLFormControlElementPrivate&>(priv()).dispatchFormControlInputEvent();
}

void
HTMLFormControlElement::dispatchFormControlChangeEvent()
{
    return static_cast<HTMLFormControlElementPrivate&>(priv()).dispatchFormControlChangeEvent();
}

HTMLFormElement*
HTMLFormControlElement::form() const
{
    return reinterpret_cast<HTMLFormControlElementPrivate&>(priv()).form();
}

} // namespace