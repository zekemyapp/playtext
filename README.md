# Playtext

A library for printing animated text in a game using the [Playdate SDK](https://play.date/dev/)

Playtext takes a list of texts and interate through it, while taking into account
moodifiers.

Right now the only modifier included is ":" for a pause in the printing process


---


## Usage

To initialize the library you should first pass a list of texts:

```
const char MY_TEXTS[] = {
  "Hello",
  "World:.:.:.::",
}
```


