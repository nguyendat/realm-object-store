////////////////////////////////////////////////////////////////////////////
//
// Copyright 2016 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#include "object.hpp"

#include "impl/object_notifier.hpp"
#include "impl/realm_coordinator.hpp"

using namespace realm;

Object::~Object() = default;

NotificationToken Object::add_notification_block(CollectionChangeCallback callback)
{
    if (!m_notifier)
        m_notifier = std::make_shared<_impl::ObjectNotifier>(m_row, m_realm);
    _impl::RealmCoordinator::register_notifier(m_notifier);
    return {m_notifier, m_notifier->add_callback(std::move(callback))};
}
