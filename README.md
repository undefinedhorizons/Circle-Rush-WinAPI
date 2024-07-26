# Circle Rush WinAPI

**Управление:**  
`ЛКМ`: изменение направления движения шариков  
`Стрелка влево` и `Стрелка вправо`: альтернативное управление направлением движения шариков  
`Space` и `Enter`: перезапуск игры  
`Esc`: выход из игры

**Билд игры:**  
[По ссылке](https://github.com/undefinedhorizons/Circle-Rush-WinAPI/releases/download/0.2/Circle-Rush-WinAPI.0.2.exe) или во вкладке Releases

**Инструкция по сборке проекта:**  
Открыть проект в Visual Studio Community 2022.

Если сразу проект не собирается, то скорее всего надо настроить Windows SDK Version и Platform Toolset. По идее, Visual Studio сам предлагает их поменять, если версии не совпадают. Так эти параметры находятся в Project->GameTemplate Properties.  
Если не подходят уже установленные версии, то можно попробовать версии, использованные мной: `Windows SDK Version==10.0`, `Platform Toolset==Visual Studio 2022 (v143)`.
