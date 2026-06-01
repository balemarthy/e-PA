# **e-PA : Lean MVP Engineering Requirements**

## **1. Introduction**

This document defines the high-level engineering requirements for the
MVP version of the e-PA (Electronic Personal Assistant) embedded
reminder device.

The purpose of this document is to establish a clear engineering
direction while intentionally avoiding premature implementation detail.

The requirements in this document are intended to:

- guide architecture discovery,

- define core system obligations,

- constrain system scope,

- support embedded software design,

- preserve implementation flexibility during architecture development.

This document does not attempt to fully specify:

- runtime architecture,

- module decomposition,

- event flow,

- interface APIs,

- scheduling algorithms,

- internal software structure.

Those concerns are expected to emerge during later architecture stages.

# **2. Product Summary**

The e-PA system is a standalone embedded reminder appliance designed to
provide scheduled spoken reminders using locally stored audio assets.

The system is intended to:

- operate continuously,

- maintain local reminder scheduling,

- support temporary internet outages,

- provide minimal user interaction,

- prioritize reliability and simplicity.

The MVP focuses on deterministic embedded behavior rather than
conversational AI functionality.

# **3. Functional Requirements**

## **FR-001 --- Reminder Playback**

The system shall announce scheduled reminders using audible voice
prompts.

## **FR-002 --- Reminder Scheduling**

The system shall trigger reminders based on locally maintained time.

## **FR-003 --- Cloud Synchronization**

The system shall periodically retrieve reminder schedules from a remote
endpoint.

## **FR-004 --- Offline Operation**

The system shall continue reminder operation during temporary internet
outages.

## **FR-005 --- User Snooze Interaction**

The system shall allow users to temporarily defer active reminders.

## **FR-006 --- Local Timekeeping**

The system shall maintain accurate local time independently of
continuous internet availability.

## **FR-007 --- Reminder Metadata Support**

The system shall support reminder information received from external
schedule data.

## **FR-008 --- Connectivity Indication**

The system shall provide visual indication of internet connectivity
state.

## **FR-009 --- Local Audio Playback**

The system shall use locally stored audio assets for reminder
announcements.

## **FR-010 --- Configuration Support**

The system shall support device configuration through a serial interface
for the MVP phase.

# **4. Non-Functional Requirements**

## **NFR-001 --- Deterministic Embedded Operation**

The firmware architecture shall prioritize deterministic embedded
execution behavior.

## **NFR-002 --- Reliability**

The system shall recover cleanly after reboot or temporary power
interruption.

## **NFR-003 --- Modularity**

The firmware shall be structured using modular software architecture
principles.

## **NFR-004 --- Testability**

The firmware architecture shall support unit testing of core application
logic.

## **NFR-005 --- Simplicity**

The MVP system shall prioritize simplicity and maintainability over
feature richness.

# **5. System Constraints**

## **SC-001 --- Embedded-First Architecture**

The MVP shall be implemented as a dedicated embedded appliance rather
than a general-purpose computing platform.

## **SC-002 --- Audio Strategy**

The MVP shall avoid runtime cloud-dependent text-to-speech synthesis.

## **SC-003 --- Interaction Scope**

The MVP shall avoid conversational voice interaction and speech
recognition functionality.

## **SC-004 --- Connectivity Model**

The system shall assume intermittent internet connectivity.

## **SC-005 --- Deployment Model**

The MVP system shall assume continuous external power operation.

# **6. Explicit MVP Non-Goals**

The MVP intentionally excludes:

- conversational AI,

- speech recognition,

- wake-word detection,

- mobile application ecosystems,

- advanced multilingual support,

- touchscreen interfaces,

- cloud AI integration,

- multimedia playback,

- arbitrary runtime text-to-speech generation.

# **7. Engineering Discovery Areas**

The following areas intentionally remain open for architectural
exploration:

- reminder lifecycle behavior,

- runtime scheduling strategy,

- persistence policy,

- audio composition architecture,

- event handling model,

- runtime concurrency model,

- watchdog strategy,

- reconnect strategy,

- reminder state management,

- future extensibility mechanisms.

These areas are expected to be refined during:

- system context modeling,

- object discovery,

- CRC analysis,

- runtime architecture design.

# **8. Intended Engineering Flow**

The expected development flow for the e-PA system is:

Product Exploration

↓

Lean Engineering Requirements

↓

System Context Modeling

↓

Object Discovery

↓

CRC Responsibility Analysis

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
