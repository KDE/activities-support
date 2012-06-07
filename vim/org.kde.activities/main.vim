if exists("loaded_KDE_ACTIVITIES")
    finish
endif

if (v:progname == "ex")
   finish
endif

let loaded_KDE_ACTIVITIES = 1

python import sys
python import vim
python sys.path.insert(0, vim.eval('expand("<sfile>:h")'))

pyfile <sfile>:h/main.py

" autocmd BufAdd      * :python kde_activities_Opened()
" autocmd BufRead     * :python kde_activities_Opened()
" autocmd BufFilePost * :python kde_activities_Opened()
"
" autocmd BufDelete   * :python kde_activities_Closed()
" autocmd BufFilePre  * :python kde_activities_Closed()

autocmd BufLeave    * :python kde_activities_FocussedOut()
autocmd BufEnter    * :python kde_activities_FocussedIn()

command KLink         :python kde_activities_Link()<CR>
command KUnlink       :python kde_activities_Unlink()<CR>
