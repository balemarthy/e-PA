# **e-PA : System Context & Problem Definition**

## **1. Introduction**

This document defines the system context, operational boundary, and
high-level problem definition for the e-PA (Electronic Personal
Assistant) embedded reminder system.

The purpose of this document is to establish a clear architectural
understanding of:

- what the system is,

- what responsibilities belong to the system,

- what entities interact with the system,

- what behaviors are expected from the system,

- what responsibilities remain external to the system.

This document intentionally focuses on:

- system behavior,

- external interactions,

- architectural boundaries,

- high-level responsibilities.

This document intentionally avoids:

- implementation details,

- task design,

- software modules,

- runtime scheduling algorithms,

- interface APIs,

- low-level firmware structure.

These concerns are expected to emerge in later architecture stages.

# **2. System Purpose**

The e-PA system is a standalone embedded reminder appliance whose
primary purpose is to deliver scheduled spoken reminders to users using
a simple, reliable, and always-available embedded platform.

The system is designed to:

- maintain local reminder schedules,

- announce reminders through audio playback,

- support temporary reminder snoozing,

- synchronize schedules from external systems,

- continue operation during temporary internet outages.

The system prioritizes:

- reliability,

- deterministic embedded behavior,

- simplicity,

- low operational complexity,

- minimal user interaction.

The system is not intended to behave as:

- a conversational AI assistant,

- a smart speaker,

- a general-purpose computing platform,

- a multimedia entertainment device.

# **3. Problem Definition**

Modern reminder systems are heavily dependent on smartphones and
application ecosystems.

However, smartphone-based reminders are often ineffective because:

- notifications may be ignored,

- devices may be muted,

- users may not actively monitor screens,

- notifications compete with unrelated content,

- some users struggle with application interfaces,

- reminder interactions may become cognitively overwhelming.

The e-PA system addresses this problem by providing:

- a dedicated reminder endpoint,

- audible reminder delivery,

- simple user interaction,

- persistent always-on operation,

- appliance-style behavior.

The product intentionally minimizes:

- user interface complexity,

- application dependency,

- runtime feature complexity,

- cloud-side dependency during normal operation.

# **4. System Boundary**

The e-PA embedded system is responsible for:

- local reminder scheduling,

- local timekeeping,

- reminder triggering,

- reminder playback,

- snooze handling,

- connectivity monitoring,

- local event handling,

- local runtime supervision,

- schedule synchronization,

- audio playback control,

- status indication.

The e-PA embedded system is NOT responsible for:

- user account management,

- cloud authentication workflows,

- schedule authoring,

- conversational AI,

- speech recognition,

- natural language processing,

- cloud orchestration,

- advanced text-to-speech synthesis,

- mobile ecosystem management.

These responsibilities intentionally remain outside the embedded
firmware boundary.

# **5. Actors**

## **5.1 Primary Human Actor**

# **User**

The user is the individual receiving reminder notifications from the
system.

The user interacts with the system through:

- listening to spoken reminders,

- pressing the snooze button,

- observing visual status indicators.

The user is not expected to perform complex device interaction.

## **5.2 Secondary Human Actor**

# **Installer / Developer**

The installer or developer is responsible for:

- initial device configuration,

- serial configuration,

- firmware flashing,

- diagnostics,

- maintenance activities.

This interaction is expected to occur infrequently.

# **6. External Systems**

## **6.1 Cloud Reminder Service**

An external cloud-connected system responsible for:

- generating reminder schedules,

- storing reminder information,

- exposing reminder data through a simplified API or JSON endpoint.

The embedded firmware consumes reminder schedules from this system but
does not own reminder generation logic.

## **6.2 Wi-Fi Network**

Provides internet connectivity between the e-PA device and external
cloud services.

The Wi-Fi network is considered unreliable and intermittently available.

The firmware must tolerate temporary connectivity loss.

## **6.3 Time Synchronization Source**

An external source used to synchronize local device time.

Examples may include:

- NTP services,

- cloud timestamps,

- network-based time references.

The system shall continue local timekeeping when this source becomes
unavailable.

# **7. High-Level Use Cases**

## **Use Case 1 --- Scheduled Reminder Playback**

1.  The system synchronizes reminder schedules.

2.  The system maintains local reminder timing.

3.  A scheduled reminder time occurs.

4.  The system announces the reminder using spoken audio.

## **Use Case 2 --- Reminder Snooze**

1.  A reminder becomes active.

2.  The user presses the snooze button.

3.  The active reminder is temporarily deferred.

4.  The reminder becomes active again after the snooze interval expires.

## **Use Case 3 --- Offline Operation**

1.  Internet connectivity becomes unavailable.

2.  The system indicates connectivity loss.

3.  The system continues local reminder operation using local schedules
    and RTC timekeeping.

## **Use Case 4 --- Schedule Synchronization**

1.  The system connects to the cloud reminder service.

2.  Updated reminder schedules are retrieved.

3.  Local scheduling information is refreshed.

## **Use Case 5 --- Power Recovery**

1.  The system reboots after power interruption.

2.  The system restores operational behavior.

3.  The system resumes normal scheduling operation.

Expired reminders are not required to persist after reboot.

# **8. Operational Assumptions**

The current MVP assumes:

- continuous external power,

- stationary deployment,

- intermittent internet connectivity,

- English-only reminder playback,

- serial-based configuration,

- local RTC availability,

- local audio asset storage,

- minimal user interaction.

The MVP intentionally avoids:

- battery optimization,

- complex UI systems,

- conversational interaction,

- advanced cloud dependency.

# **9. High-Level System Responsibilities**

At a behavioral level, the e-PA system is expected to:

- maintain local operational time,

- monitor reminder schedules,

- trigger reminders,

- manage reminder states,

- process user snooze interactions,

- synchronize external schedules,

- monitor connectivity state,

- control audio playback,

- supervise runtime operation.

These responsibilities are expected to guide future architecture
decomposition activities.

# **10. High-Level Interaction Model**

The e-PA system operates primarily as an event-driven embedded
appliance.

The dominant runtime stimuli are expected to include:

- timer expirations,

- scheduled reminder events,

- button presses,

- connectivity changes,

- synchronization events,

- reboot and recovery events.

The architecture is therefore expected to evolve toward:

- event-driven execution,

- timer-based scheduling,

- state-driven reminder handling,

- asynchronous event processing.

# **11. Context Diagram**

+\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--+

\| Cloud Reminder \|

\| Service \|

+\-\-\-\-\-\-\-\-\--+\-\-\-\-\-\-\-\-\-\--+

\|

\| Reminder Schedule

\| JSON Data

\|

+\-\-\-\-\-\-\-\--v\-\-\-\-\-\-\-\-\--+

\| e-PA \|

\| Embedded Reminder \|

\| Appliance \|

+\-\-\--+\-\-\-\-\-\-\-\-\--+\-\-\--+

\| \|

Snooze Button \| \| Audio Playback

\| \|

+\-\-\-\-\--v\--+ +\--v\-\-\-\-\--+

\| User \| \| Speaker \|

+\-\-\-\-\-\-\-\--+ +\-\-\-\-\-\-\-\--+

\|

\| Wi-Fi Connectivity

\|

+\-\-\-\-\--v\-\-\-\-\--+

\| Wi-Fi / \|

\| Internet \|

+\-\-\-\-\-\-\-\-\-\-\-\--+

\|

\| Time Synchronization

\|

+\-\-\-\-\--v\-\-\-\-\--+

\| Time Source \|

+\-\-\-\-\-\-\-\-\-\-\-\--+

# **12. Architectural Observations**

The current architecture direction strongly suggests that the firmware
should evolve into:

An Event-Driven Embedded Runtime System

rather than:

A Conversational AI System

This distinction significantly reduces:

- runtime complexity,

- cloud dependency,

- memory requirements,

- processing requirements,

- implementation risk.

The architecture direction favors:

- deterministic execution,

- modular responsibilities,

- lightweight runtime coordination,

- embedded-friendly implementation.

# **13. Areas Requiring Further Architecture Discovery**

The following areas remain intentionally unresolved and are expected to
drive future architecture exploration:

- reminder lifecycle states,

- scheduling policies,

- runtime event handling,

- persistence strategy,

- reconnect behavior,

- reminder overlap handling,

- watchdog supervision,

- audio composition architecture,

- reminder prioritization,

- runtime concurrency requirements.

These questions are intentionally deferred to later architecture stages.

# **14. Transition Toward Object Discovery**

This document establishes the system boundary and problem context
required for the next architecture stage.

The next stage is expected to focus on:

Level-1 Responsibility Object Discovery

The purpose of that stage will be to identify:

- major system responsibility objects,

- behavioral ownership,

- collaborations between responsibilities,

- cohesive architectural decomposition.

The architecture process intentionally proceeds from:

- system responsibilities\
  to:

- object responsibilities\
  before implementation structure is introduced.
