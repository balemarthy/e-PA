# **e-PA : Embedded Product Exploration & Architecture Discovery**

## **1. Introduction**

The e-PA (Electronic Personal Assistant) is envisioned as a standalone
embedded voice reminder device designed to provide scheduled spoken
reminders in a reliable, simple, and distraction-free manner.

Unlike smartphones or conversational AI assistants, the e-PA is intended
to operate as a focused embedded appliance whose primary purpose is to
help users remember important scheduled activities through audible
prompts.

The system is intentionally designed around embedded system principles:

- deterministic behavior,

- low-cost hardware,

- minimal user interaction,

- high reliability,

- simple deployment,

- always-available operation.

This document is not a formal requirements specification.

Instead, it serves as a product exploration and architecture discovery
document intended to:

- explore the problem space,

- clarify product intent,

- expose architectural concerns,

- identify ambiguities,

- guide engineering discussions,

- stimulate system-level thinking before implementation begins.

# **2. Product Vision**

The e-PA device acts as a dedicated reminder endpoint capable of:

- retrieving scheduled reminders,

- maintaining accurate local time,

- announcing reminders using spoken audio,

- allowing users to temporarily snooze reminders,

- continuing operation even during temporary internet outages.

The reminder categories are intentionally generic and extensible.

Possible reminder use cases include:

- medicine reminders,

- hydration reminders,

- meetings,

- prayer times,

- exercise prompts,

- study schedules,

- daily routines,

- custom user-defined reminders,

- personal task notifications.

The system is designed to behave as a simple embedded assistant rather
than a conversational AI product.

# **3. Problem Context**

Modern reminder systems are heavily smartphone-dependent.

However, smartphone notifications are frequently ineffective because:

- notifications are ignored,

- devices are muted,

- users are distracted,

- users may not actively monitor screens,

- elderly users may struggle with applications,

- notifications compete with unrelated content.

A dedicated reminder appliance provides advantages such as:

- persistent audible alerts,

- simplified operation,

- reduced interaction complexity,

- dedicated reminder-focused behavior,

- always-on operation,

- improved accessibility for non-technical users.

The e-PA system aims to solve these limitations using a focused embedded
device architecture.

# **4. Intended User Experience**

The expected user experience is intentionally simple.

## **Example Workflow**

1.  The device periodically synchronizes reminder schedules from a
    cloud-connected source.

2.  Reminder schedules are received as lightweight JSON payloads.

3.  The device maintains local time using an RTC.

4.  When a reminder time occurs:

    - the device plays an audible reminder,

    - reminder details are announced,

    - the user may press a snooze button.

5.  If snoozed:

    - the reminder is deferred temporarily,

    - the reminder is replayed after the snooze interval expires.

6.  If the user does not snooze:

    - the reminder eventually times out and stops.

7.  If internet connectivity is lost:

    - the device continues local operation,

    - a status LED indicates connectivity loss.

The device intentionally minimizes:

- menus,

- configuration complexity,

- UI interaction,

- learning curve.

# **5. MVP Scope**

The MVP currently includes:

- scheduled reminder playback,

- Wi-Fi connectivity,

- reminder synchronization,

- local RTC-based timekeeping,

- snooze button handling,

- speaker audio output,

- LED status indication,

- serial-based configuration,

- English-only audio prompts,

- local audio asset playback,

- runtime reminder playback from JSON-derived content.

The MVP intentionally prioritizes:

- simplicity,

- reliability,

- architectural clarity,

- rapid prototyping.

# **6. Explicit Non-Goals**

The MVP intentionally excludes:

- speech recognition,

- wake-word detection,

- conversational AI,

- natural language understanding,

- cloud AI integration,

- touchscreen interfaces,

- multimedia playback,

- mobile application ecosystems,

- arbitrary runtime text-to-speech generation,

- complex user account systems,

- advanced multilingual support,

- large-scale cloud orchestration.

The system is not intended to compete with smart speakers or voice
assistants.

# **7. High-Level System Behavior**

At a behavioral level, the system operates as an event-driven embedded
appliance.

Core runtime responsibilities include:

- maintaining time,

- tracking scheduled reminders,

- monitoring connectivity,

- managing reminder states,

- handling snooze events,

- controlling audio playback,

- synchronizing schedules,

- supervising runtime operation.

The system naturally evolves toward:

- event-driven architecture,

- timer-driven behavior,

- state-based reminder management,

- asynchronous event handling.

# **8. Proposed Hardware Direction**

The current hardware direction is based around an ESP32-class MCU
platform.

Expected hardware elements include:

- ESP32-S3 MCU,

- external RTC,

- I²S audio amplifier,

- speaker,

- Wi-Fi connectivity,

- flash storage,

- snooze button,

- status LED,

- serial configuration interface.

The hardware is expected to support:

- always-on operation,

- low BOM cost,

- reliable embedded execution,

- local audio playback.

# **9. Audio System Direction**

The MVP avoids traditional text-to-speech synthesis.

Instead, the system is expected to use:

- pre-recorded audio clips,

- local audio storage,

- runtime audio stitching/composition.

This approach:

- reduces complexity,

- lowers compute requirements,

- improves determinism,

- simplifies multilingual expansion later.

Reminder announcements may include:

- time values,

- reminder labels,

- user-defined reminder metadata.

The exact audio composition strategy remains an active architecture
discussion area.

# **10. Connectivity Model**

The current architecture assumes:

- Wi-Fi-based cloud synchronization,

- intermittent internet connectivity,

- local offline operation during outages,

- RTC-backed local time continuity.

The system should continue functioning even when disconnected from the
internet temporarily.

Connectivity loss is indicated through a dedicated LED status indicator.

# **11. Power Model**

The MVP currently assumes:

- continuous external power,

- always-on operation,

- no aggressive low-power sleep optimization,

- stationary deployment.

Battery optimization is not considered a primary MVP concern at this
stage.

# **12. Architectural Direction**

The system is currently best characterized as:

## **Event-Driven Embedded Reminder Appliance**

NOT:

## **Conversational AI Assistant**

This distinction is extremely important because it fundamentally changes
the architecture complexity.

The current direction intentionally favors:

- deterministic embedded behavior,

- bounded runtime complexity,

- modular event handling,

- lightweight firmware architecture.

# **13. Open Engineering Questions**

The following questions remain intentionally unresolved and are expected
to drive architectural discovery during subsequent engineering stages.

## **13.1 Reminder Lifecycle**

- What defines reminder completion?

- Should reminders repeat before timeout?

- Can reminders overlap?

- What is the maximum snooze duration?

- Can reminders be canceled remotely?

## **13.2 Runtime Scheduling**

- How many simultaneous reminders must be supported?

- What timing precision is required?

- What is the acceptable reminder latency?

- How are missed reminders handled after reboot?

## **13.3 Persistence Strategy**

- Which runtime data must survive reboot?

- Should active snoozed reminders persist?

- How frequently should schedules be synchronized?

- What is the flash storage strategy?

## **13.4 Audio Architecture**

- How should dynamic reminder labels be handled?

- What audio formats should be supported?

- Should audio playback be streamed or buffered?

- What is the maximum reminder duration?

- How should future multilingual support be organized?

## **13.5 Connectivity Behavior**

- What happens during extended internet loss?

- How frequently should reconnect attempts occur?

- What happens if cloud synchronization fails?

- Should stale schedules remain active?

## **13.6 Reliability Expectations**

- What happens after unexpected reboot?

- What watchdog strategy is required?

- What defines acceptable system uptime?

- How are runtime faults detected and reported?

## **13.7 User Interaction**

- Are additional buttons required later?

- Is local reminder editing required?

- Should brightness or volume be adjustable?

- How should accessibility be handled?

# **14. Questions an Embedded Architect Would Ask**

An embedded architect reviewing this system would naturally ask
questions such as:

- What are the true system boundaries?

- What responsibilities belong inside firmware?

- What should remain cloud-side?

- What are the hard real-time constraints?

- Which events are timing critical?

- What happens during partial failure?

- What are the runtime states of a reminder?

- What events drive system execution?

- How is event ordering managed?

- What data must remain persistent?

- What is the expected concurrency model?

- How should audio playback be isolated?

- What watchdog recovery strategy exists?

- How is system health supervised?

- What runtime architecture best matches the workload?

These questions are intentionally important because they guide the
transition from:

- product idea\
  to:

- engineering architecture.

# **15. Transition Toward Engineering Requirements**

This document intentionally captures:

- ideas,

- assumptions,

- operational concepts,

- open questions,

- architecture-driving concerns.

It is expected that future engineering activities will refine this
exploration into:

- functional requirements,

- non-functional requirements,

- runtime constraints,

- interface specifications,

- hardware requirements,

- software architecture artifacts.

The purpose of this document is therefore not to finalize implementation
details, but rather to establish a shared understanding of the product
vision and the architectural discovery process required to realize it.

# **16. Intended Engineering Workflow**

The expected engineering flow for the e-PA system is:

Product Exploration

↓

Architecture Discovery

↓

Requirements Definition

↓

Object Modeling

↓

Event Modeling

↓

Runtime Architecture

↓

Module Design

↓

Implementation

↓

Testing & Validation
