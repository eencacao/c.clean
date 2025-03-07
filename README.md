# CLEAN

### Exercise: Simple User Management System

An application with the following layers:  
- Entities (Domain Layer) → Pure business logic, independent of frameworks.   
- Use Cases (Application Layer) → Orchestrates business logic and defines application behavior.   
- Adapters (Interface Layer) → Controllers, presenters, and UI elements.   
- Infrastructure (Data Layer) → External services (database, APIs, frameworks).     

```
./
│── src/
│   ├── entities/                          # Domain models
│   │   ├── user.h
│   ├── usecases/                          # Application logic
│   │   ├── user_service.h
│   │   ├── user_service.c
│   ├── interfaces/                        # Adapters (Repository, Controllers)
│   │   ├── user_repository.h
│   ├── infrastructure/                    # Implementation (DB, UI)
│   │   ├── in_memory_user_repository.h
│   │   ├── in_memory_user_repository.c
│   ├── main.c                             # Entry point
│── .gitignore
│── LICENSE
│── README.md
└── Makefile
```