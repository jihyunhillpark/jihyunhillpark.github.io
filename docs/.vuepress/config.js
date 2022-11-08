import { defaultTheme } from '@vuepress/theme-default'

export default {
  locales: {
    '/': {
      lang: 'en-US',
      title: 'jihyunee blog',
      description: 'jihyun\'s dev&tech blog'
    },
  },
  theme: defaultTheme({
    sidebar: 'auto',
  }),
}
