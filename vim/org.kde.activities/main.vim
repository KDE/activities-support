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

command LinkToActivity              :python kde_activities_Link()<CR>
command UnlinkFromActivity          :python kde_activities_Unlink()<CR>
command LinkDirectoryToActivity     :python kde_activities_LinkDirectory()<CR>
command UnlinkDirectoryFromActivity :python kde_activities_UnlinkDirectory()<CR>

menu File.Activities.Link\ current\ file :LinkToActivity<CR>
menu File.Activities.Link\ containing\ directory     :LinkDirectoryToActivity<CR>
menu File.Activities.Unlink\ current\ file :UnlinkFromActivity<CR>
menu File.Activities.Unlink\ containing\ directory     :UnlinkDirectoryFromActivity<CR>