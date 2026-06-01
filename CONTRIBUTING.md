# Contributing to e-PA Firmware

Thank you for contributing to the e-PA Firmware project.

This repository is both an embedded firmware project and a software architecture learning platform.

Contributors are encouraged not only to write code but also to understand the architectural decisions behind the code.

---

# Project Philosophy

The primary goal of this repository is to demonstrate a structured embedded software development methodology.

The workflow follows:

Problem Understanding

→ Requirements Discovery

→ Context Modeling

→ Object Modeling

→ CRC Analysis

→ Event Modeling

→ Runtime Architecture

→ Module Design

→ Interface Design

→ Verification Strategy

→ Implementation

Architecture is considered a first-class deliverable.

---

# Before Writing Code

Contributors should understand:

* Problem Statement
* Context Diagram
* Object Models
* CRC Analysis
* Event Model
* Runtime Architecture
* Module Design

before beginning implementation.

Code should be derived from architecture.

Architecture should not be reverse-engineered from code.

---

# Contribution Areas

Contributors may participate in:

## Architecture

Examples:

* Architecture reviews
* Design improvements
* Responsibility analysis
* Event model improvements
* Runtime behavior discussions

---

## Interface Design

Examples:

* API refinement
* Ownership improvements
* Dependency reduction
* Interface simplification

---

## Implementation

Examples:

* Runtime infrastructure
* State machines
* Event dispatching
* Scheduling services
* Connectivity services

---

## Verification

Examples:

* Unit testing
* Integration testing
* Mock framework development
* Verification automation

---

# Engineering Rules

## Rule 1

Respect module ownership.

Each module should own a single clear responsibility.

Avoid creating "god modules".

---

## Rule 2

Prefer event-driven interactions.

Avoid direct module-to-module coupling when semantic events are appropriate.

---

## Rule 3

Avoid global shared state.

State should remain owned by the module responsible for it.

---

## Rule 4

Prefer static allocation.

Dynamic memory allocation should not be introduced without architectural review.

---

## Rule 5

Keep platform dependencies isolated.

Application logic should never directly depend on hardware drivers.

---

## Rule 6

Design for testability.

Interfaces should support mocking and host-side testing.

---

# Header File First Development

The project follows an interface-first approach.

The expected sequence is:

1. Architecture approved
2. Interface approved
3. Verification intent understood
4. Implementation begins

Implementation should not start before the corresponding interface specification exists.

---

# Pull Request Guidelines

A pull request should answer:

* What problem is being solved?
* Which architectural artifact does it relate to?
* Does it introduce new responsibilities?
* Does it change ownership boundaries?
* Does it introduce new dependencies?
* How will it be verified?

---

# Code Review Expectations

Reviewers should evaluate:

## Architectural Quality

* Responsibility ownership
* Coupling
* Cohesion
* Scalability

## Interface Quality

* API clarity
* Encapsulation
* Dependency management

## Implementation Quality

* Readability
* Maintainability
* Determinism
* Reliability

---

# Testing Expectations

Every implementation contribution should identify:

* What behavior is being verified
* Which architectural responsibility is being validated
* What edge cases should be considered

Contributors are encouraged to derive test implementations from the TDD & Verification Specification artifact.

---

# Learning Mindset

This repository is intentionally structured as a teaching project.

Contributors are encouraged to:

* Ask architectural questions
* Challenge assumptions
* Explore alternatives
* Justify design decisions

The objective is not simply to produce firmware.

The objective is to learn how professional embedded software systems are designed.

---

# Final Principle

Understand the responsibility before implementing the solution.

Understand the behavior before writing the code.

Understand the architecture before modifying the system.
