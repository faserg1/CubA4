#pragma once

// Expressions should be like:
// 100vh + 50ppc - 12cpc
// Where
// vh - viewport height in percentage (like absolute height)
// ppc is parent percent
// cpc is content percent

// Expressions should have cache (lazy) and markAsDirty when need to be calculated again