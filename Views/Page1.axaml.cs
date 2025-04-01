using System;
using Avalonia;
using Avalonia.Animation;
using Avalonia.Animation.Easings;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Layout;
using MAAtools.ViewModels;

namespace MAAtools.Views
{
    public partial class Page1 : UserControl
    {
        public void Set_MainGrd_Sytle(){
                Page1_MainGrid.Width=900;
        }

        public void Set_Grid_Sytle(){
            Page1_Grid0.Height=320;
            Page1_Grid0.Width=160;

            Page1_Grid1.Height=320;
            Page1_Grid1.Width=160;

            Page1_Grid2.Height=40;
            Page1_Grid2.Width=160;
            // Page1_Grid0.Margin=new Thickness(-140,-180,0,0);
        }

        public void OnButtonClick(object sender, RoutedEventArgs e){
            Console.WriteLine("Button Clicked");
    // 你的事件处理逻辑
        }
        public Page1()
        {
            InitializeComponent();
            Set_MainGrd_Sytle();
            Set_Grid_Sytle();
             this.DataContext = new Page1ViewModel();
        }
    }
}