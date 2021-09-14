# Style Guide

### Directories
- Directory name should be lowercase in camel_case (if needed): ``directory_name`` or ``name``

### Files
- File name should be lowercase in camel_case (if needed): ``file_name`` or ``name``

### Tests
- File names of tests should be ``t_component``

### Classes  
- Each class should contain Initialize method
- Class members should be in camel_case with m prefix: ``m_class_member``
- Class names should be in PascalCase: ``ClassName``
- Class methods should be in PascalCase: ``ClassMethod``

### Constants
- Constant values in the cpp files should be declared with ``constexpr``
- Constant names should start with k prefix in PascalCase: ``kConstantName``

### Namespaces
- Namespace name should be in PascalCase: ``NamespaceName``
- Namespace functions should be in PascalCase: ``NamespaceFunction``

### Structures
- Structure names should be in PascalCase: ``StructureName``
- Structure members should be in camel_case: ``structure_member``

### Enums
- Enum name should be in PascalCase: ``EnumName``
- Enum fields should start with k prefix in PascalCase: ``kEnumField``

### Functions
- Regular functions should be in camel_case: ``function_name``

### Documentation
- Each function or method should contain brief and parameter explaination
- Documentation files should be .md files in HIGHERCASE inside the documentation/ directory: ``documentation/DOCUMENT.md``